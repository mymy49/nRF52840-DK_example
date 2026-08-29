/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file config.h
 * @brief System-wide configuration header for the yss RTOS on nRF52840-DK (runtime example).
 *
 * This file provides compile-time configuration macros for the yss real-time
 * operating system and the application peripherals used in the runtime
 * measurement example. Modify the values here to tune the scheduler,
 * enable/disable peripherals, and adjust hardware settings.
 *
 * @note Copy this file to your project's include path (app/inc) and rename
 *       it to config.h before use.
 */

#ifndef YSS_CONFIG__H_
#define YSS_CONFIG__H_

// =====================================================================
// External Crystal Clock Configuration
// =====================================================================
/// @brief Defines the external high-speed clock (HSE) frequency in Hz.
///
/// When this macro is defined, the PLL is configured using the external
/// crystal (HSE) as its clock source. If left undefined, the internal
/// oscillator (HSI) is used instead.
/// The crystal frequency must be a multiple of 4 MHz.
//#define HSE_CLOCK_FREQ 12000000

// =====================================================================
// Scheduler Configuration
// =====================================================================
/// @brief Selects the hardware timer used by the yss runtime scheduler.
///
/// Specifies which TIMER peripheral drives the RTOS tick and manages
/// thread preemption. Valid values are RUNTIME_TIMER0 through RUNTIME_TIMER5.
/// This timer is consumed exclusively by the RTOS and must not be used
/// as a general-purpose timer by the application.
#define YSS_RUNTIME_TIMER	RUNTIME_TIMER0

/// @brief Selects the hardware timer used by the yss delay functions.
///
/// Specifies which TIMER peripheral is used to implement blocking and
/// non-blocking delay functions (e.g., thread::delay(), thread::delayUs()).
/// Valid values are DELAY_TIMER0 through DELAY_TIMER4.
/// This timer must be different from the one assigned to YSS_RUNTIME_TIMER.
#define YSS_DELAY_TIMER		DELAY_TIMER1

/// @brief Number of SysTick clocks allocated per thread time-slice.
///
/// Each thread is granted this many SysTick counts before the scheduler
/// considers preempting it. A higher value gives each thread more CPU time
/// per slice.
#define THREAD_GIVEN_CLOCK	20000

/// @brief Maximum number of threads that can be registered simultaneously.
///
/// Determines the size of the internal thread control-block table. Increase
/// this value if the application requires more concurrent threads.
#define MAX_THREAD			16

/// @brief Fills each thread stack with the 0xAA pattern on creation.
///
/// When set to true, the initial stack memory of every thread is pre-filled
/// with 0xAA. This is useful for measuring peak stack usage during debugging.
/// Set to false in production builds to save startup time.
#define FILL_THREAD_STACK	false

// =====================================================================
// GUI Library Configuration
// =====================================================================
/// @brief Enables the yss graphical user interface (GUI) library.
///
/// Set to true to compile in the GUI subsystem. This example does not use
/// a display, so the GUI library is disabled.
#define USE_GUI				false

// =====================================================================
// Key (Button) Configuration
// =====================================================================
/// @brief Maximum number of key objects that can be created.
///
/// Set to 0 to disable the key (button) subsystem entirely.
/// Increase this value to match the number of physical buttons used.
#define NUM_OF_YSS_KEY		0

// =====================================================================
// Peripheral Enable/Disable Configuration
// =====================================================================
// Set each macro to true to enable the corresponding peripheral, or
// false to disable it. Disabled peripherals consume no RAM or clock.

// --- BPWM ---
/// @brief Enables BPWM0 peripheral.
#define BPWM0_ENABLE		false

/// @brief Enables BPWM1 peripheral.
#define BPWM1_ENABLE		false

// --- EADC ---
/// @brief Enables the Enhanced ADC (EADC) peripheral.
#define EADC_ENABLE			true

// --- I2C ---
/// @brief Enables I2C0 peripheral.
#define I2C0_ENABLE			false

/// @brief Enables I2C1 peripheral.
#define I2C1_ENABLE			false

// --- I2S ---
/// @brief Enables I2S0 peripheral.
#define I2S0_ENABLE			false

// --- PWM ---
/// @brief Enables PWM0 peripheral.
#define PWM0_ENABLE			false

/// @brief Enables PWM1 peripheral.
#define PWM1_ENABLE			false

/// @brief Enables PWM2 peripheral.
#define PWM2_ENABLE			false

/// @brief Enables PWM3 peripheral.
#define PWM3_ENABLE			false

// --- QSPI ---
/// @brief Enables QSPI0 peripheral.
#define	QSPI0_ENABLE		true

// --- SPI ---
/// @brief Enables SPI0 peripheral.
#define SPI0_ENABLE			false

// --- TIMER ---
/// @brief Enables TIMER0 peripheral. Disabled here; TIMER0 is reserved for the runtime scheduler.
#define TIMER0_ENABLE		false

/// @brief Enables TIMER1 peripheral. Disabled here; TIMER1 is reserved for the delay timer (YSS_DELAY_TIMER).
#define TIMER1_ENABLE		false

/// @brief Enables TIMER2 peripheral.
#define TIMER2_ENABLE		false

/// @brief Enables TIMER3 peripheral.
#define TIMER3_ENABLE		false

// --- UART ---
/// @brief Enables UART0 peripheral.
#define UART0_ENABLE		false

/// @brief Enables UART1 peripheral.
#define UART1_ENABLE		false

/// @brief Enables UART2 peripheral.
#define UART2_ENABLE		false

// --- USCI ---
/// @brief Enables USCI SPI0 (USPI0) peripheral.
#define USPI0_ENABLE		false

/// @brief Enables USCI UART0 (UUART0) peripheral.
#define UUART0_ENABLE		true

#endif

