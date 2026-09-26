/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file config.h
 * @brief System-wide configuration header for the yss RTOS on nRF52840-DK (UART example).
 *
 * This file provides compile-time configuration macros for the yss real-time
 * operating system and the application peripherals used in the UART loopback
 * and echo example. Modify the values here to tune the scheduler,
 * enable/disable peripherals, and adjust hardware settings.
 */

#ifndef YSS_CONFIG__H_
#define YSS_CONFIG__H_

// =====================================================================
// High-Frequency Crystal Oscillator (HFXO) Configuration
// =====================================================================
/// @brief Enables the external 32 MHz high-frequency crystal oscillator (HFXO).
///
/// When set to true, the system clock is sourced from the external crystal
/// rather than the internal RC oscillator, providing higher accuracy.
/// The crystal frequency must be a multiple of 4 MHz.
#define USE_HFXO				true

// =====================================================================
// Scheduler Configuration
// =====================================================================
/// @brief Selects the hardware timer used by the yss runtime scheduler.
///
/// Specifies which TIMER peripheral drives the RTOS tick and manages
/// thread preemption. Valid values are RUNTIME_TIMER0 through RUNTIME_TIMER5.
/// This timer is consumed exclusively by the RTOS and must not be used
/// as a general-purpose timer by the application.
#define YSS_RUNTIME_TIMER		RUNTIME_TIMER0

/// @brief Selects the hardware timer used by the yss delay functions.
///
/// Specifies which TIMER peripheral is used to implement blocking and
/// non-blocking delay functions (e.g., thread::delay(), thread::delayUs()).
/// Valid values are DELAY_TIMER0 through DELAY_TIMER4.
/// This timer must be different from the one assigned to YSS_RUNTIME_TIMER.
#define YSS_DELAY_TIMER			DELAY_TIMER1

/// @brief Number of SysTick clocks allocated per thread time-slice.
///
/// Each thread is granted this many SysTick counts before the scheduler
/// considers preempting it. A higher value gives each thread more CPU time
/// per slice.
#define THREAD_GIVEN_CLOCK		20000

/// @brief Maximum number of threads that can be registered simultaneously.
///
/// Determines the size of the internal thread control-block table. Increase
/// this value if the application requires more concurrent threads.
#define MAX_THREAD				16

/// @brief Fills each thread stack with the 0xAA pattern on creation.
///
/// When set to true, the initial stack memory of every thread is pre-filled
/// with 0xAA. This is useful for measuring peak stack usage during debugging.
/// Set to false in production builds to save startup time.
#define FILL_THREAD_STACK		false

// =====================================================================
// GUI Library Configuration
// =====================================================================
/// @brief Enables the yss graphical user interface (GUI) library.
///
/// Set to true to compile in the GUI subsystem. This example does not use
/// a display, so the GUI library is disabled.
#define USE_GUI					false

// =====================================================================
// Key (Button) Configuration
// =====================================================================
/// @brief Maximum number of key objects that can be created.
///
/// Set to 0 to disable the key (button) subsystem entirely.
/// Increase this value to match the number of physical buttons used.
#define NUM_OF_YSS_KEY			0

// =====================================================================
// Peripheral Enable/Disable Configuration
// =====================================================================
// Set each macro to true to enable the corresponding peripheral, or
// false to disable it. Disabled peripherals consume no RAM or clock.

// --- TIMER ---
/// @brief Enables TIMER0 peripheral. Disabled here; TIMER0 is reserved for the runtime scheduler.
#define TIMER0_ENABLE			false

/// @brief Enables TIMER1 peripheral. Disabled here; TIMER1 is reserved for the delay timer (YSS_DELAY_TIMER).
#define TIMER1_ENABLE			false

/// @brief Enables TIMER2 peripheral.
#define TIMER2_ENABLE			false

/// @brief Enables TIMER3 peripheral.
#define TIMER3_ENABLE			false

/// @brief Enables TIMER4 peripheral.
#define TIMER4_ENABLE			false

// --- RADIO ---
#define RADIO_ENABLE			true

// --- UART ---
/// @brief Enables UART0 peripheral. Used in this example for serial communication at 115200 baud.
#define UART0_ENABLE			true

#endif

