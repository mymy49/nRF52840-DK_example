/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the nRF52840-DK LED blink example.
 *
 * This example demonstrates multi-threaded LED blinking using the yss RTOS.
 * Four independent threads are created, each toggling one of the four on-board
 * LEDs of the nRF52840-DK at different frequencies:
 *   - LED1: 1 Hz   (500 ms ON / 500 ms OFF)
 *   - LED2: 2 Hz   (250 ms ON / 250 ms OFF)
 *   - LED3: 4 Hz   (125 ms ON / 125 ms OFF)
 *   - LED4: 8 Hz   (62.5 ms ON / 62.5 ms OFF via microsecond delay)
 *
 * Each thread runs an infinite loop and uses thread::delay() or
 * thread::delayUs() to yield CPU time to other threads while waiting.
 */

#include <yss.h>          ///< yss RTOS main header (OS primitives, thread API, etc.)
#include <bsp.h>          ///< Board Support Package (LED, peripheral initialization)
#include <yss/debug.h>    ///< yss debug utilities (e.g., debug print over SWO/UART)
#include <util/runtime.h> ///< Runtime scheduler utility functions

/**
 * @brief Thread function that blinks LED1 at 1 Hz.
 *
 * Toggles LED1 ON for 500 ms and OFF for 500 ms in an infinite loop,
 * yielding the CPU to other threads during each delay period.
 */
void thread_blinkLed1(void)
{
	while(1)
	{
		led::setLed1(true);     ///< Turn LED1 on
		thread::delay(500);     ///< Wait 500 ms (yields CPU to other threads)

		led::setLed1(false);    ///< Turn LED1 off
		thread::delay(500);     ///< Wait 500 ms (yields CPU to other threads)
	}
}

/**
 * @brief Thread function that blinks LED2 at 2 Hz.
 *
 * Toggles LED2 ON for 250 ms and OFF for 250 ms in an infinite loop,
 * yielding the CPU to other threads during each delay period.
 */
void thread_blinkLed2(void)
{
	while(1)
	{
		led::setLed2(true);     ///< Turn LED2 on
		thread::delay(250);     ///< Wait 250 ms (yields CPU to other threads)

		led::setLed2(false);    ///< Turn LED2 off
		thread::delay(250);     ///< Wait 250 ms (yields CPU to other threads)
	}
}

/**
 * @brief Thread function that blinks LED3 at 4 Hz.
 *
 * Toggles LED3 ON for 125 ms and OFF for 125 ms in an infinite loop,
 * yielding the CPU to other threads during each delay period.
 */
void thread_blinkLed3(void)
{
	while(1)
	{
		led::setLed3(true);     ///< Turn LED3 on
		thread::delay(125);     ///< Wait 125 ms (yields CPU to other threads)

		led::setLed3(false);    ///< Turn LED3 off
		thread::delay(125);     ///< Wait 125 ms (yields CPU to other threads)
	}
}

/**
 * @brief Thread function that blinks LED4 at 8 Hz using microsecond delay.
 *
 * Toggles LED4 ON for 62,500 µs and OFF for 62,500 µs in an infinite loop.
 * Uses thread::delayUs() (microsecond resolution) rather than thread::delay()
 * (millisecond resolution) to achieve the shorter half-period accurately.
 */
void thread_blinkLed4(void)
{
	while(1)
	{
		led::setLed4(true);         ///< Turn LED4 on
		thread::delayUs(62500);     ///< Wait 62,500 µs = 62.5 ms (yields CPU to other threads)

		led::setLed4(false);        ///< Turn LED4 off
		thread::delayUs(62500);     ///< Wait 62,500 µs = 62.5 ms (yields CPU to other threads)
	}
}

/**
 * @brief Application entry point.
 *
 * Performs the following startup sequence:
 *   1. Initializes the yss RTOS kernel (clocks, scheduler, SysTick, etc.).
 *   2. Initializes board-level peripherals (LEDs) via initializeBoard().
 *   3. Creates four LED blink threads, each allocated a 512-byte stack.
 *   4. Enters an idle loop, continuously yielding to allow the scheduler
 *      to run the registered threads.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	initializeYss();        ///< Initialize the yss RTOS kernel (must be called first)

	initializeBoard();      ///< Initialize board peripherals (LEDs, etc.)

	/// Register LED blink threads. Each thread receives a 512-byte stack.
	thread::add(thread_blinkLed1, 512);  ///< Add LED1 blink thread (1 Hz)
	thread::add(thread_blinkLed2, 512);  ///< Add LED2 blink thread (2 Hz)
	thread::add(thread_blinkLed3, 512);  ///< Add LED3 blink thread (4 Hz)
	thread::add(thread_blinkLed4, 512);  ///< Add LED4 blink thread (8 Hz)

	/// Idle loop: the main thread continuously yields so the scheduler
	/// can execute the LED blink threads round-robin.
	while(1)
	{
		thread::yield();    ///< Yield CPU time to other runnable threads
	}
}


