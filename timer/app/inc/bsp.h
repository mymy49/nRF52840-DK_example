/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) header for the nRF52840-DK timer example.
 *
 * This header declares the board-level initialization interface used to set up
 * the hardware timers (TIMER2, TIMER3, TIMER4) and their interrupt service
 * routines for the timer counting demonstration.
 */

#ifndef BSP__H_
#define BSP__H_

#include <stdint.h>   ///< Standard integer type definitions (uint8_t, uint32_t, etc.)

/**
 * @brief Initializes all on-board peripherals and hardware timers.
 *
 * Configures and starts TIMER2, TIMER3, and TIMER4 with different update
 * frequencies, and attaches an ISR to each timer to increment the
 * corresponding global counter variable on every tick.
 *
 * Timer frequencies configured in this BSP:
 *   - TIMER2: 1,000 Hz  (update period: 1 ms)
 *   - TIMER3: 10,000 Hz (update period: 100 µs)
 *   - TIMER4: 100,000 Hz (update period: 10 µs)
 *
 * @note Call initializeYss() before calling this function.
 */
void initializeBoard(void);

#endif

