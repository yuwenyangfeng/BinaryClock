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
	// declare variables
	int _hr = hour();
	int _minute = minute();
	unsigned int debounce = 300; // set debounce time
	unsigned long int previous = millis() - debounce;
	// judge set-button triger// must be 'if' not 'while'
	if (digitalRead(SET) == LOW)
	{
		while (digitalRead(SET) == LOW); // eliminate dithering on real, cancel it when proteus VSM debug
		// go in setup mode:
		BinaryClock_Seconds(0); // turn off seconds display
		do
		{
			BinaryClock_Hour(_hr); // display hour-in set mode
			while ((digitalRead(ADD) == LOW) && ((millis() - previous) > debounce))
			// compare debounce need the same type is int.
			{
				if (_hr < 12)
				{
					_hr = _hr + 1;
					previous = millis(); // refresh previous vairable
				}
				else
				{
					_hr = 1;
					previous = millis(); // refresh previous vairable
				}
			}
		}
		while (digitalRead(SET) == HIGH); // when set is HIGH, cycle in do...while
	}
	// must be 'if' not 'while'
	if (digitalRead(SET) == LOW)
	{
		while (digitalRead(SET) == LOW); // eliminate dithering on real, cancel it when proteus VSM debug
		BinaryClock_Seconds(0); // turn off seconds display
		do
		{
			BinaryClock_Minute(_minute);
			debounce=200;
			while ((digitalRead(ADD) == LOW) && ((millis() - previous) > debounce))
			{
				if (_minute < 60)
				{
					_minute = _minute + 1;
					previous = millis();
				}
				else
				{
					_minute = 1;
					previous = millis();
				}
			}
		}
		while (digitalRead(SET) == HIGH); // when set is HIGH, cycle in do...while
		setTime(_hr, _minute, 0, 12, 12, 2012); // must be stay in do while ,else no display, will be drop in this line directly,when set-button unpushed.
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
