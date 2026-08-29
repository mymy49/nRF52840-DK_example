/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the nRF52840-DK timer example.
 *
 * This file initializes three hardware timers (TIMER2, TIMER3, TIMER4) at
 * different frequencies and attaches a dedicated ISR to each. Each ISR
 * increments a global floating-point counter by a fixed step, allowing
 * the main application to observe and compare hardware timer accuracy against
 * software thread counters.
 *
 * Timer configurations:
 *   - TIMER2: 1,000 Hz  → counter step 0.000001 per tick  (effective: 0.001 /s)
 *   - TIMER3: 10,000 Hz → counter step 0.000001 per tick  (effective: 0.01 /s)
 *   - TIMER4: 100,000 Hz → counter step 0.000001 per tick (effective: 0.1 /s)
 */

#include <bsp.h>           ///< BSP interface declarations
#include <yss/instance.h>  ///< yss RTOS peripheral instance declarations (timer2, timer3, timer4)

/// @brief Accumulated elapsed time counter driven by TIMER2 (1,000 Hz).
///
/// Incremented by 0.000001 on each TIMER2 update interrupt (1,000 times/s),
/// resulting in an effective increment rate of 0.001 per second.
/// Declared volatile because it is modified inside an ISR.
volatile float gTimer2Counter;

/// @brief Accumulated elapsed time counter driven by TIMER3 (10,000 Hz).
///
/// Incremented by 0.000001 on each TIMER3 update interrupt (10,000 times/s),
/// resulting in an effective increment rate of 0.01 per second.
/// Declared volatile because it is modified inside an ISR.
volatile float gTimer3Counter;

/// @brief Accumulated elapsed time counter driven by TIMER4 (100,000 Hz).
///
/// Incremented by 0.000001 on each TIMER4 update interrupt (100,000 times/s),
/// resulting in an effective increment rate of 0.1 per second.
/// Declared volatile because it is modified inside an ISR.
volatile float gTimer4Counter;

/**
 * @brief TIMER2 update interrupt service routine.
 *
 * Called at 1,000 Hz by the hardware. Increments gTimer2Counter by 0.000001
 * on each invocation.
 */
void isr_timer2(void)
{
	gTimer2Counter += 0.000001f;
}

/**
 * @brief TIMER3 update interrupt service routine.
 *
 * Called at 10,000 Hz by the hardware. Increments gTimer3Counter by 0.000001
 * on each invocation.
 */
void isr_timer3(void)
{
	gTimer3Counter += 0.000001f;
}

/**
 * @brief TIMER4 update interrupt service routine.
 *
 * Called at 100,000 Hz by the hardware. Increments gTimer4Counter by 0.000001
 * on each invocation.
 */
void isr_timer4(void)
{
	gTimer4Counter += 0.000001f;
}

/**
 * @brief Initializes all on-board peripherals and hardware timers.
 *
 * Enables the peripheral clock, initializes the timer with its target
 * update frequency, registers the ISR, enables the interrupt, and starts
 * each of TIMER2, TIMER3, and TIMER4.
 *
 * Timer update frequencies:
 *   - TIMER2: initialized at 1,000 Hz  (1 ms period)
 *   - TIMER3: initialized at 10,000 Hz (100 µs period)
 *   - TIMER4: initialized at 100,000 Hz (10 µs period)
 */
void initializeBoard(void)
{
	timer2.enableClock();               ///< Enable peripheral clock for TIMER2
	timer2.initialize(1000);            ///< Set TIMER2 update frequency to 1,000 Hz
	timer2.setIsrForUpdate(isr_timer2); ///< Register ISR called on each TIMER2 update event
	timer2.enableInterrupt();           ///< Enable TIMER2 update interrupt in NVIC
	timer2.start();                     ///< Start TIMER2 counting

	timer3.enableClock();               ///< Enable peripheral clock for TIMER3
	timer3.initialize(10000);           ///< Set TIMER3 update frequency to 10,000 Hz
	timer3.setIsrForUpdate(isr_timer3); ///< Register ISR called on each TIMER3 update event
	timer3.enableInterrupt();           ///< Enable TIMER3 update interrupt in NVIC
	timer3.start();                     ///< Start TIMER3 counting

	timer4.enableClock();               ///< Enable peripheral clock for TIMER4
	timer4.initialize(100000);          ///< Set TIMER4 update frequency to 100,000 Hz
	timer4.setIsrForUpdate(isr_timer4); ///< Register ISR called on each TIMER4 update event
	timer4.enableInterrupt();           ///< Enable TIMER4 update interrupt in NVIC
	timer4.start();                     ///< Start TIMER4 counting
}

