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
#include <string.h>
#include <stdio.h>

triggerId_t gTriggerTxLed, gTriggerRxLed;

void trigger_handleTxLed()
{
	led::setLed1(true);
	thread::delay(20);
	led::setLed1(false);
}

void thread_sendUart0(void)
{
	const char *str = "Hello Word!!\n\r";
	char sendBuf[128];
	uint32_t len = strlen(str);
	uint32_t i = 0;

	while(1)
	{
		sprintf(sendBuf, "\n\rHello Word!! %d", i++);
		len = strlen(sendBuf);

		trigger::run(gTriggerTxLed);
		uart0.send(sendBuf, len);

		thread::delay(1000);
	}
}

void trigger_handleRxLed()
{
	led::setLed2(true);
	thread::delay(20);
	led::setLed2(false);
}

int main(void)
{
	uint32_t count;
	int8_t *rxbuf;

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	gTriggerTxLed = trigger::add(trigger_handleTxLed, 512);
	thread::add(thread_sendUart0, 2048);

	gTriggerRxLed  = trigger::add(trigger_handleRxLed, 512);

	while(1)
	{
		count = uart0.getRxCount();
		if(count > 0)
		{
			rxbuf = uart0.getRxBuffer();

			for(uint32_t i = 0; i < count; i++)
			{
				debug_putchar(rxbuf[i]);
			}

			trigger::run(gTriggerRxLed);

			uart0.releaseRxBuffer(count);
		}

		thread::yield();
	}
}


