/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the nRF52840-DK LED blink example.
 *
 * This file implements the board-level initialization routine. It serves as the
 * single entry point for setting up all hardware peripherals specific to the
 * nRF52840-DK development kit used in this example.
 */

#include <bsp.h>           ///< BSP interface declarations
#include <yss/instance.h>  ///< yss RTOS peripheral instance declarations

/**
 * @brief Initializes all on-board peripherals.
 *
 * Currently initializes the LED subsystem by calling led::initialize(),
 * which configures the GPIO pins connected to the four on-board LEDs of
 * the nRF52840-DK as outputs and sets them to the default off state.
 *
 * Additional peripheral initialization (e.g., UART, SPI) should be added
 * here as the project grows.
 */
void initializeBoard(void)
{
	led::initialize();  ///< Configure on-board LED GPIO pins as outputs
}

