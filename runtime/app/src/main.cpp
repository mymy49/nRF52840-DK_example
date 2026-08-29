/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the nRF52840-DK runtime measurement example.
 *
 * This example demonstrates how to use the yss RTOS runtime module to obtain
 * a monotonically increasing millisecond timestamp (runtime::getMsec()) and
 * continuously print it over a debug output channel (e.g., SWO, UART).
 *
 * Unlike the LED blink example, no additional threads are created — the
 * measurement loop runs directly from the main context, yielding via the
 * implicit cooperative scheduling of debug_printf().
 */

#include <yss.h>          ///< yss RTOS main header (OS primitives, thread API, etc.)
#include <bsp.h>          ///< Board Support Package (peripheral initialization)
#include <yss/debug.h>    ///< yss debug utilities (debug_printf over SWO/UART)
#include <util/runtime.h> ///< Runtime module providing runtime::getMsec() and getMicro()

/**
 * @brief Application entry point.
 *
 * Performs the following startup sequence:
 *   1. Initializes the yss RTOS kernel (clocks, scheduler, SysTick, etc.).
 *   2. Initializes board-level peripherals via initializeBoard().
 *   3. Enters an infinite loop that reads the current millisecond timestamp
 *      from runtime::getMsec() and prints it continuously via debug_printf().
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	initializeYss();        ///< Initialize the yss RTOS kernel (must be called first)

	initializeBoard();      ///< Initialize board peripherals

	while(1)
	{
		/// Continuously print the elapsed time in milliseconds since boot.
		/// runtime::getMsec() returns a uint64_t cast here to uint32_t for formatting.
		debug_printf("%d\r", (uint32_t)runtime::getMsec());
	}
}


