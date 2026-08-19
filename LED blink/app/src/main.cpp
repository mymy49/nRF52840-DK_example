/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include <yss/debug.h>
#include <util/runtime.h>

void thread_blinkLed1(void)
{
	while(1)
	{
		led::setLed1(true);
		thread::delay(500);

		led::setLed1(false);
		thread::delay(500);
	}
}

void thread_blinkLed2(void)
{
	while(1)
	{
		led::setLed2(true);
		thread::delay(250);

		led::setLed2(false);
		thread::delay(250);
	}
}

void thread_blinkLed3(void)
{
	while(1)
	{
		led::setLed3(true);
		thread::delay(125);

		led::setLed3(false);
		thread::delay(125);
	}
}

void thread_blinkLed4(void)
{
	while(1)
	{
		led::setLed4(true);
		thread::delayUs(62500);

		led::setLed4(false);
		thread::delayUs(62500);
	}
}

int main(void)
{
	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_blinkLed1, 512);
	thread::add(thread_blinkLed2, 512);
	thread::add(thread_blinkLed3, 512);
	thread::add(thread_blinkLed4, 512);

	while(1)
	{
		thread::yield();
	}
}


