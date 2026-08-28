/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

volatile float gTimer2Counter, gTimer3Counter, gTimer4Counter;

void isr_timer2(void)
{
	gTimer2Counter += 0.000001f;
}

void isr_timer3(void)
{
	gTimer3Counter += 0.000001f;
}

void isr_timer4(void)
{
	gTimer4Counter += 0.000001f;
}

void initializeBoard(void)
{
	timer2.enableClock();
	timer2.initialize(1000);
	timer2.setIsrForUpdate(isr_timer2);
	timer2.enableInterrupt();
	timer2.start();

	timer3.enableClock();
	timer3.initialize(10000);
	timer3.setIsrForUpdate(isr_timer3);
	timer3.enableInterrupt();
	timer3.start();

	timer4.enableClock();
	timer4.initialize(100000);
	timer4.setIsrForUpdate(isr_timer4);
	timer4.enableInterrupt();
	timer4.start();
}

