/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the nRF52840-DK timer example.
 *
 * This example demonstrates hardware timer accuracy by running three hardware
 * timers (TIMER2, TIMER3, TIMER4) alongside three software counter threads.
 * A dedicated print thread periodically outputs all six counter values via
 * debug_printf(), allowing direct comparison of hardware interrupt-driven
 * counters vs. software thread-based counters.
 *
 * Thread overview:
 *   - thread_count1 : Performs floating-point arithmetic in a tight loop
 *                     to simulate CPU-intensive work; updates gThread1Counter.
 *   - thread_count2 : Simple additive counter; increments gThread2Counter.
 *   - thread_count3 : Simple additive counter; increments gThread3Counter.
 *   - thread_print  : Prints all six counter values (3 SW threads + 3 HW timers).
 *
 * Hardware timer ISR counters (defined in bsp.cpp):
 *   - gTimer2Counter : driven by TIMER2 at 1,000 Hz
 *   - gTimer3Counter : driven by TIMER3 at 10,000 Hz
 *   - gTimer4Counter : driven by TIMER4 at 100,000 Hz
 */

#include <yss.h>          ///< yss RTOS main header (OS primitives, thread API, etc.)
#include <bsp.h>          ///< Board Support Package (timer initialization, ISR counters)
#include <yss/debug.h>    ///< yss debug utilities (debug_printf over SWO/UART)
#include <util/runtime.h> ///< Runtime module providing runtime::getMsec()

/// @brief External references to the hardware timer ISR counters defined in bsp.cpp.
extern volatile float gTimer2Counter, gTimer3Counter, gTimer4Counter;

/// @brief Software counter updated continuously by thread_count1.
///
/// Uses floating-point arithmetic to simulate a CPU-intensive workload.
/// Declared volatile to prevent the compiler from optimizing away cross-thread reads.
volatile float gThread1Counter;

/// @brief Software counter updated continuously by thread_count2.
///
/// Incremented by 0.00001 per loop iteration to provide a reference
/// software counting rate. Declared volatile for cross-thread visibility.
volatile float gThread2Counter;

/// @brief Software counter updated continuously by thread_count3.
///
/// Incremented by 0.000001 per loop iteration to provide a reference
/// software counting rate. Declared volatile for cross-thread visibility.
volatile float gThread3Counter;

/**
 * @brief Thread function that performs floating-point computation in a tight loop.
 *
 * Simulates CPU-intensive work by repeatedly multiplying and adding a local
 * floating-point variable, then publishing the result to gThread1Counter.
 * When the accumulated value exceeds 100.0, it resets to the initial seed value
 * to prevent overflow.
 *
 * This thread is useful for observing how the RTOS scheduler interleaves
 * CPU-bound threads with interrupt-driven hardware timer counters.
 */
void thread_count1(void)
{
    float x = 0.1234567f;  ///< Local accumulator with an arbitrary non-zero seed

    while(1)
    {
        x = x * 1.00001f + 0.000001f;  ///< Multiply-accumulate to simulate FPU workload

        if(x > 100.0f)
            x = 0.1234567f;   ///< Reset to seed value when the limit is exceeded

        gThread1Counter = x;  ///< Publish the current accumulator value for the print thread
    }
}

/**
 * @brief Thread function that increments gThread2Counter in a tight loop.
 *
 * Provides a simple software reference counter to compare against the
 * hardware timer-driven counters. Increments by 0.00001 per iteration.
 */
void thread_count2(void)
{
	while(1)
		gThread2Counter += 0.00001f;  ///< Increment software counter by 0.00001 per loop
}

/**
 * @brief Thread function that increments gThread3Counter in a tight loop.
 *
 * Provides a simple software reference counter to compare against the
 * hardware timer-driven counters. Increments by 0.000001 per iteration.
 */
void thread_count3(void)
{
	while(1)
		gThread3Counter += 0.000001f;  ///< Increment software counter by 0.000001 per loop
}

/**
 * @brief Thread function that prints all counter values continuously.
 *
 * Outputs a comma-separated line containing:
 *   1. Elapsed time in milliseconds (runtime::getMsec(), cast to uint32_t)
 *   2. gThread1Counter — FPU workload thread counter
 *   3. gThread2Counter — simple software counter (thread_count2)
 *   4. gThread3Counter — simple software counter (thread_count3)
 *   5. gTimer2Counter  — hardware TIMER2 ISR counter (1,000 Hz)
 *   6. gTimer3Counter  — hardware TIMER3 ISR counter (10,000 Hz)
 *   7. gTimer4Counter  — hardware TIMER4 ISR counter (100,000 Hz)
 *
 * @note The format string uses %f for float values and %d for the ms timestamp.
 *       Output is sent to the debug channel (SWO or UART).
 */
void thread_print(void)
{
	while(1)
	{
		debug_printf("%f, %f, %f, %f, %f, %f\r",
			(uint32_t)runtime::getMsec(),  ///< Elapsed time in ms since boot
			gThread1Counter,               ///< FPU workload thread counter
			gThread2Counter,               ///< Software counter (thread_count2)
			gThread3Counter,               ///< Software counter (thread_count3)
			gTimer2Counter,                ///< HW TIMER2 counter (1,000 Hz)
			gTimer3Counter,                ///< HW TIMER3 counter (10,000 Hz)
			gTimer4Counter);               ///< HW TIMER4 counter (100,000 Hz)
	}
}

/**
 * @brief Application entry point.
 *
 * Performs the following startup sequence:
 *   1. Initializes the yss RTOS kernel (clocks, scheduler, SysTick, etc.).
 *   2. Initializes board-level peripherals (TIMER2, TIMER3, TIMER4) via initializeBoard().
 *   3. Creates four threads (print, count1, count2, count3), each with a 512-byte stack.
 *   4. Enters an idle loop, continuously yielding to allow the scheduler
 *      to run the registered threads.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	initializeYss();        ///< Initialize the yss RTOS kernel (must be called first)

	initializeBoard();      ///< Initialize board peripherals (TIMER2, TIMER3, TIMER4)

	/// Register threads. Each thread receives a 512-byte stack.
	thread::add(thread_print,  512);  ///< Add print thread (outputs all counter values)
	thread::add(thread_count1, 512);  ///< Add FPU workload counter thread
	thread::add(thread_count2, 512);  ///< Add simple software counter thread 2
	thread::add(thread_count3, 512);  ///< Add simple software counter thread 3

	/// Idle loop: the main thread continuously yields so the scheduler
	/// can execute the registered threads round-robin.
	while(1)
	{
		thread::yield();    ///< Yield CPU time to other runnable threads
	}
}


