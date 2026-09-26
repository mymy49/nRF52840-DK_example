/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) header for the nRF52840-DK UART example.
 *
 * This header declares the board-level initialization interface used to set up
 * the on-board LED drivers and the UART0 peripheral (GPIO pin muxing,
 * baud rate, stop bits, parity, and interrupt configuration).
 */

#ifndef BSP__H_
#define BSP__H_

#include <stdint.h>   ///< Standard integer type definitions (uint8_t, uint32_t, etc.)
#include <dev/led.h>  ///< LED device driver interface
#include <bluetooth/Ble4p0.h>

extern Ble4p0 ble;

/**
 * @brief Initializes all on-board peripherals required by the UART example.
 *
 * Performs the following setup steps:
 *   1. Initializes the on-board LED driver (LED1 = TX indicator, LED2 = RX indicator).
 *   2. Configures GPIO0 pins 5-8 as UART0 alternate functions
 *      (RTS, TXD, CTS, RXD respectively).
 *   3. Initializes UART0 at 115200 baud, 1 stop bit, no parity, no hardware
 *      flow control, with a 64-byte receive ring buffer.
 *   4. Enables the UART0 receive interrupt.
 *
 * @note Call initializeYss() before calling this function.
 */
void initializeBoard(void);

#endif

