/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

void initializeBoard(void)
{
	led::initialize();

	// UART0
	gpio0.setAsAltFunc(5, Gpio::UART0_RTS);
	gpio0.setAsAltFunc(6, Gpio::UART0_TXD);
	gpio0.setAsAltFunc(7, Gpio::UART0_CTS);
	gpio0.setAsAltFunc(8, Gpio::UART0_RXD);

	Uart::config_t uart0Config =
	{
		Uart::MODE_NORMAL,		//mode_t mode;			// 동작 모드의 종류를 설정합니다.
		115200,					//uint32_t baudrate;	// 보레이트를 설정합니다.
		Uart::STOP_1BIT,		//stopbit_t stopbit;	// Stop Bit의 종류를 설정합니다.
		Uart::PARITY_NONE,		//parityBit_t parity;	// 패리티 비트를 설정합니다.
		false,					//bool hwfc;
		nullptr,				//void *rcvBuf;			// 수신 버퍼를 설정합니다.
		64,						//uint32_t rcvBufSize;	// 수신 버퍼의 크기를 설정합니다.
	};

	uart0.enableClock();
	uart0.initialize(uart0Config);
	uart0.enableInterrupt();
}

