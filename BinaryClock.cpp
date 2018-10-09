#include "BinaryClock.h"
#include <Time.h>
#include <TimeLib.h>
// initial port
void BinaryClock_Port()
{
	for (int i = 0; i <= 15; ++i)
	{
		pinMode(i, OUTPUT); // LEDs
	}
	pinMode(SET, INPUT_PULLUP); // Set Button pull-up
	pinMode(ADD, INPUT_PULLUP); // Add Button pull-up
}



// method: octal is binary too on pc, use bit-move opration.
void BinaryClock_Hour(int Hr)
{
	int _hr = Hr;
	int _port = H8; // 'H8' was Macro define in BinaryClock.h
	int _bit = 3;
	// decimal is composed by binary,the method is bit opration
	// octal-'10' transfer binary-'1010'
	while (_bit >= 0)
	{
		if ((_hr >> _bit) & 1)
		// while number move right ?bit & 1 is TRUE LED light
		{
			digitalWrite(_port, HIGH);
		}
		else
		{
			digitalWrite(_port, LOW);
		}
		--_bit;
		++_port;
	}
}

// ///////////////////////////////////////
void BinaryClock_Minute(int Min)
{
	int _min = Min;
	int _port = M32; // 'M32' was Macro define in BinaryClock.h
	int _bit = 5; // be used for bit move, there are 6 leds display minute.
	while (_bit >= 0)
	{
		if ((_min >> _bit) & 1)
		{
			digitalWrite(_port, HIGH);
		}
		else
		{
			digitalWrite(_port, LOW);
		}
		--_bit;
		++_port;
	}
}

// //////////////////////////////////////////
void BinaryClock_Seconds(int Sec)
{
	int _sec = Sec;
	int _port = S32;
	int _bit = 5;
	while (_bit >= 0)
	{
		if ((_sec >> _bit) & 1)
		{
			digitalWrite(_port, HIGH);
		}
		else
		{
			digitalWrite(_port, LOW);
		}
		--_bit;
		++_port;
	}
}
