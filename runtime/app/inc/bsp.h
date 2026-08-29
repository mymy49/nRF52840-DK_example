/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) header for the nRF52840-DK runtime example.
 *
 * This header declares the board-level initialization interface used to set up
 * all on-board peripherals required by the runtime measurement application.
 */

#ifndef BSP__H_
#define BSP__H_

#include <stdint.h>   ///< Standard integer type definitions (uint8_t, uint32_t, etc.)

/**
 * @brief Initializes all on-board peripherals.
 *
 * This function must be called once during system startup, after the RTOS
 * (yss) has been initialized. It performs hardware-specific setup for all
 * peripherals declared in the BSP for this example.
 *
 * @note Call initializeYss() before calling this function.
 */
void initializeBoard(void);

#endif

