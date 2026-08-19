/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <dev/led.h>
#include <yss/instance.h>

namespace led 
{
	void initialize(void)
	{
		gpio0.setAsOutput(13);
		gpio0.setAsOutput(14);
		gpio0.setAsOutput(15);
		gpio0.setAsOutput(16);

		setLed1(false);
		setLed2(false);
		setLed3(false);
		setLed4(false);
	}

	void setLed1(bool on)
	{
		gpio0.setOutput(13, !on);
	}

	void setLed2(bool on)
	{
		gpio0.setOutput(14, !on);
	}

	void setLed3(bool on)
	{
		gpio0.setOutput(15, !on);
	}

	void setLed4(bool on)
	{
		gpio0.setOutput(16, !on);
	}
}
