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

extern uint32_t gTimer1Counter, gTimer2Counter, gTimer3Counter, gTimer4Counter;

int main(void)
{
	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	while(1)
	{
		debug_printf("%d, %d, %d, %d, %d\r",
			(uint32_t)runtime::getMsec(),
			gTimer1Counter,   // timer1: 10 Hz
			gTimer2Counter,   // timer2: 100 Hz
			gTimer3Counter,   // timer3: 1 kHz
			gTimer4Counter);  // timer4: 10 kHz  (CPU1)
	}
}


