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

// method
void BinaryClock_Set() // set time as you want
{
	if ((digitalRead(SET) == LOW))
	{
		BinaryClock_Seconds(0); // turn off Seconds' display-dropped in set mode
		bool _flag = false; // --tag
		int _hr = hour();
		int _min = minute();
		do
		{
			BinaryClock_Hour(_hr); // display hour-in set mode
			if (digitalRead(ADD) == LOW)
			// add button be trigger
			{
				_flag = true; // --overturn tag
				if (_hr < 11)
					_hr = _hr + 1;
				else
					_hr = 0;
				delay(300); // Elimination Buffeting of Keystroke
			}
			if ((digitalRead(SET)) == LOW && (_flag == true))
				break;
		}
		while (1);
		_flag = false;
		do
		{
			BinaryClock_Minute(_min);
			if (digitalRead(ADD) == LOW)
			{
				_flag = true;
				if (_min < 59)
					_min = _min + 1;
				else
					_min = 0;
				delay(300);
			}
			if ((digitalRead(SET)) == LOW && (_flag == true))
				break;
		}
		while (1);
		setTime(_hr, _min, 0, 12, 12, 2012);
		delay(1000); // must be existed, this delay forbit back to head line
	}
}

// /////////////////////////////////////
void BinaryClock_Hour(int Hr)
{
	int _hr = Hr;
	int _port = H8;
	int _bit = 3;
	while (_bit >= 0)
	{
		if ((_hr >> _bit) & 1)
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
	int _port = M32;
	int _bit = 5;
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
