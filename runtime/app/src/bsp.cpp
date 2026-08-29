/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the nRF52840-DK runtime example.
 *
 * This file implements the board-level initialization routine. It serves as the
 * single entry point for setting up all hardware peripherals specific to the
 * nRF52840-DK development kit used in this runtime measurement example.
 */

#include <bsp.h>           ///< BSP interface declarations
#include <yss/instance.h>  ///< yss RTOS peripheral instance declarations

/**
 * @brief Initializes all on-board peripherals.
 *
 * Currently a stub — no peripheral initialization is required for this
 * runtime measurement example. Additional peripheral setup (e.g., UART,
 * SPI, LED) should be added here as the project grows.
 */
void initializeBoard(void)
{

}

