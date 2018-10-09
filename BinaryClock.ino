#include <Time.h>
#include <TimeLib.h>
#include "BinaryClock.h"
void setup()
{
	BinaryClock_Port();
	hourFormat12();
}

void loop()
{
	// method:SET TIME
	void BinaryClock_Set();
	BinaryClock_Hour(hour());
	BinaryClock_Minute(minute());
	BinaryClock_Seconds(second());
}

void BinaryClock_Set() // set time as you want
{
	int _hr = hour();
	BinaryClock_Seconds(0); // turn off Seconds' display-dropped in set mode
	do
	{
		BinaryClock_Hour(_hr); // display hour-in set mode
		if (digitalRead(ADD) == LOW)
		// add button be trigger
		{
			if (_hr < 11)
				_hr = _hr + 1;
			else
				_hr = 0;
			delay(300); // Elimination Buffeting of Keystroke
		}
	}
	while (digitalRead(SET) == HIGH);
	while (digitalRead(SET) == LOW);
}
