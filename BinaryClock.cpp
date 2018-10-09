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

// method:SET TIME
void BinaryClock_Set() // set time as you want
{
	int _hr = hour();
	int _minute = minute();
	unsigned long previous = millis() - 500;
	if (digitalRead(SET) == LOW)
	{
		while (digitalRead(SET) == LOW); // eliminate dithering, cancel it when proteus VSM debug
		do
		{
			BinaryClock_Hour(_hr); // display hour-in set mode
			BinaryClock_Seconds(0);
			while ((digitalRead(ADD) == LOW) && ((millis() - previous) > 500))
			{
				if (_hr < 11)
				{
					_hr = _hr + 1;
					previous = millis();
				}
				else
				{
					_hr = 0;
					previous = millis();
				}
			}
		}
		while (digitalRead(SET) == HIGH); // when set is HIGH, cycle in do...while
	}
	if (digitalRead(SET) == LOW)
	{
		while (digitalRead(SET) == LOW);
		do
		{
			BinaryClock_Minute(_minute);
			BinaryClock_Seconds(0);
			while ((digitalRead(ADD) == LOW) && ((millis() - previous) > 500))
			{
				if (_minute < 59)
				{
					_minute = _minute + 1;
					previous = millis();
				}
				else
				{
					_minute = 0;
					previous = millis();
				}
			}
		}
		while (digitalRead(SET) == HIGH); // when set is HIGH, cycle in do...while
		setTime(_hr, _minute, 0, 12, 12, 2012);
	}
	while (digitalRead(SET) == LOW); // eliminate dithering, cancel it when proteus VSM debug
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
