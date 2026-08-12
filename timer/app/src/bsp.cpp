/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

uint32_t gTimer1Counter, gTimer2Counter, gTimer3Counter, gTimer4Counter;

void isr_timer1(void)
{
	gTimer1Counter++;
}

void isr_timer2(void)
{
	gTimer2Counter++;
}

void isr_timer3(void)
{
	gTimer3Counter++;
}

void isr_timer4(void)
{
	gTimer4Counter++;
}

void initializeBoard(void)
{
	timer1.enableClock();
	timer1.initialize(100);
	timer1.setIsrForUpdate(isr_timer1);
	timer1.enableInterrupt();
	timer1.start();

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

