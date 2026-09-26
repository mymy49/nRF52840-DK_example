/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the nRF52840-DK UART example.
 *
 * This example demonstrates UART0 serial communication on the nRF52840-DK
 * using the yss RTOS. It features:
 *   - A transmit thread (thread_sendUart0) that sends an incrementing
 *     "Hello Word!!" message over UART0 every 1 second.
 *   - A main-loop RX poller that echoes received bytes to the debug output
 *     and triggers a brief LED flash on each received frame.
 *   - Two trigger handlers that blink LED1 (TX) and LED2 (RX) for 20 ms
 *     each time data is transmitted or received.
 *
 * Hardware connections (configured in bsp.cpp):
 *   - P0.06 → UART0 TXD
 *   - P0.08 → UART0 RXD
 *   - P0.05 → UART0 RTS (unused, hardware flow control disabled)
 *   - P0.07 → UART0 CTS (unused, hardware flow control disabled)
 *   - LED1 → TX activity indicator
 *   - LED2 → RX activity indicator
 */

#include <yss.h>          ///< yss RTOS main header (OS primitives, thread/trigger API, etc.)
#include <bsp.h>          ///< Board Support Package (UART0 and LED initialization)
#include <yss/debug.h>    ///< yss debug utilities (debug_putchar over SWO/UART)
#include <util/runtime.h> ///< Runtime module providing runtime::getMsec()
#include <string.h>       ///< C standard string functions (strlen)
#include <stdio.h>        ///< C standard I/O functions (sprintf)

/// @brief Trigger ID for the TX LED blink handler.
///
/// Registered via trigger::add(). Fire this trigger after transmitting data
/// to blink LED1 for 20 ms as a visual TX activity indicator.
triggerId_t gTriggerTxLed;

/// @brief Trigger ID for the RX LED blink handler.
///
/// Registered via trigger::add(). Fire this trigger after receiving data
/// to blink LED2 for 20 ms as a visual RX activity indicator.
triggerId_t gTriggerRxLed;

/**
 * @brief Trigger handler that blinks LED1 (TX indicator) for 20 ms.
 *
 * Called asynchronously by the yss trigger subsystem whenever
 * trigger::run(gTriggerTxLed) is invoked by thread_sendUart0.
 * Turns LED1 on, waits 20 ms, then turns it off.
 */
void trigger_handleTxLed()
{
	led::setLed1(true);   ///< Turn TX indicator LED1 on
	thread::delay(20);    ///< Hold LED1 on for 20 ms
	led::setLed1(false);  ///< Turn TX indicator LED1 off
}

/**
 * @brief Thread function that periodically sends a message over UART0.
 *
 * Formats an incrementing "Hello Word!! N" string into a local buffer,
 * fires the TX LED trigger to indicate transmission activity, sends the
 * string over UART0, then sleeps for 1 second before repeating.
 *
 * @note The transmit buffer is 128 bytes; ensure the formatted string
 *       does not exceed this size.
 */
void thread_sendUart0(void)
{
	const char *str = "Hello Word!!\n\r";  ///< Initial string (unused after first iteration)
	char sendBuf[128];                     ///< Local buffer for the formatted output string
	uint32_t len = strlen(str);            ///< Length of the string to send
	uint32_t i = 0;                        ///< Incrementing message counter

	while(1)
	{
		sprintf(sendBuf, "\n\rHello Word!! %d", i++);  ///< Format the message with counter value
		len = strlen(sendBuf);                          ///< Recalculate string length after formatting

		trigger::run(gTriggerTxLed);     ///< Blink LED1 to indicate TX activity
		uart0.send(sendBuf, len);        ///< Transmit the formatted string over UART0

		thread::delay(100);             ///< Wait 1 second before the next transmission
	}
}

/**
 * @brief Trigger handler that blinks LED2 (RX indicator) for 20 ms.
 *
 * Called asynchronously by the yss trigger subsystem whenever
 * trigger::run(gTriggerRxLed) is invoked by the main RX polling loop.
 * Turns LED2 on, waits 20 ms, then turns it off.
 */
void trigger_handleRxLed()
{
	led::setLed2(true);   ///< Turn RX indicator LED2 on
	thread::delay(20);    ///< Hold LED2 on for 20 ms
	led::setLed2(false);  ///< Turn RX indicator LED2 off
}

/**
 * @brief Application entry point.
 *
 * Performs the following startup sequence:
 *   1. Initializes the yss RTOS kernel (clocks, scheduler, SysTick, etc.).
 *   2. Initializes board-level peripherals (LEDs, UART0) via initializeBoard().
 *   3. Registers the TX LED trigger handler and the UART0 transmit thread.
 *   4. Registers the RX LED trigger handler.
 *   5. Enters a polling loop that checks for received UART0 data, echoes each
 *      byte to the debug output, fires the RX LED trigger, releases the
 *      receive buffer, and yields the CPU.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
 {
	uint32_t count;   ///< Number of bytes currently available in the UART0 receive buffer
	int8_t *rxbuf;    ///< Pointer to the UART0 receive ring buffer

	initializeYss();        ///< Initialize the yss RTOS kernel (must be called first)

	initializeBoard();      ///< Initialize board peripherals (LEDs and UART0)

	//gTriggerTxLed = trigger::add(trigger_handleTxLed, 512); ///< Register TX LED trigger (512-byte stack)
	//thread::add(thread_sendUart0, 2048);                     ///< Add UART0 transmit thread (2048-byte stack)

	//gTriggerRxLed = trigger::add(trigger_handleRxLed, 512); ///< Register RX LED trigger (512-byte stack)

	while(1)
	{
		thread::yield(); // 다른 스레드에게 양보	
	}
}


