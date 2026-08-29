/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the nRF52840-DK UART example.
 *
 * This file initializes the on-board LED driver and the UART0 peripheral.
 * GPIO0 pins 5-8 are configured as UART0 alternate functions, and UART0 is
 * set up for 115200 baud serial communication with a 64-byte receive buffer.
 * LED1 is used as a TX activity indicator and LED2 as an RX activity indicator.
 */

#include <bsp.h>           ///< BSP interface declarations
#include <yss/instance.h>  ///< yss RTOS peripheral instance declarations (gpio0, uart0)

/**
 * @brief Initializes all on-board peripherals required by the UART example.
 *
 * Setup sequence:
 *   1. Initializes the LED driver for TX/RX activity indication.
 *   2. Configures GPIO0 pins 5-8 as UART0 alternate functions.
 *   3. Fills a Uart::config_t structure with the desired UART0 settings.
 *   4. Enables the UART0 peripheral clock, applies the configuration,
 *      and enables the UART0 receive interrupt.
 */
void initializeBoard(void)
{
	led::initialize();  ///< Initialize on-board LEDs (LED1=TX indicator, LED2=RX indicator)

	// Configure GPIO0 pins as UART0 alternate functions
	gpio0.setAsAltFunc(5, Gpio::UART0_RTS);  ///< P0.05 → UART0 RTS (Request To Send)
	gpio0.setAsAltFunc(6, Gpio::UART0_TXD);  ///< P0.06 → UART0 TXD (Transmit Data)
	gpio0.setAsAltFunc(7, Gpio::UART0_CTS);  ///< P0.07 → UART0 CTS (Clear To Send)
	gpio0.setAsAltFunc(8, Gpio::UART0_RXD);  ///< P0.08 → UART0 RXD (Receive Data)

	/// UART0 configuration structure
	Uart::config_t uart0Config =
	{
		Uart::MODE_NORMAL,   ///< mode     : Normal UART mode (no flow control handled at protocol level)
		115200,              ///< baudrate : Communication speed in bits per second
		Uart::STOP_1BIT,     ///< stopbit  : 1 stop bit per frame
		Uart::PARITY_NONE,   ///< parity   : No parity bit
		false,               ///< hwfc     : Hardware flow control disabled
		nullptr,             ///< rcvBuf   : Use internal ring buffer (nullptr = default allocation)
		64,                  ///< rcvBufSize : Receive ring buffer size in bytes
	};

	uart0.enableClock();           ///< Enable peripheral clock for UART0
	uart0.initialize(uart0Config); ///< Apply the UART0 configuration
	uart0.enableInterrupt();       ///< Enable UART0 receive interrupt in NVIC
}

