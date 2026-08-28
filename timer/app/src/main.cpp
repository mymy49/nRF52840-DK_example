/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include <yss/debug.h>
#include <util/runtime.h>

extern volatile float gTimer2Counter, gTimer3Counter, gTimer4Counter;
volatile float gThread1Counter, gThread2Counter, gThread3Counter;

void thread_count1(void)
{
    float x = 0.1234567f;

    while(1)
    {
        x = x * 1.00001f + 0.000001f;

        if(x > 100.0f)
            x = 0.1234567f;

        gThread1Counter = x;
    }
}

void thread_count2(void)
{
	while(1)
		gThread2Counter += 0.00001f;
}

void thread_count3(void)
{
	while(1)
		gThread3Counter += 0.000001f;
}

void thread_print(void)
{
	while(1)
	{
		debug_printf("%f, %f, %f, %f, %f, %f\r",
			(uint32_t)runtime::getMsec(),
			gThread1Counter,
			gThread2Counter,
			gThread3Counter,
			gTimer2Counter,   // timer2: 100 Hz
			gTimer3Counter,   // timer3: 1 kHz
			gTimer4Counter);  // timer4: 10 kHz  (CPU1)
	}
}

int main(void)
{
	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_print, 512);
	thread::add(thread_count1, 512);
	thread::add(thread_count2, 512);
	thread::add(thread_count3, 512);

	while(1)
	{
		thread::yield();
	}
}


