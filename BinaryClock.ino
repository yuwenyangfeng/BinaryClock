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
	BinaryClock_Set();
	BinaryClock_Hour(hour());
	BinaryClock_Minute(minute());
	BinaryClock_Seconds(second());
}

void BinaryClock_Set() // set time as you want
{
	while (digitalRead(SET) == LOW)
	{
		while (digitalRead(SET) == LOW);//eliminate dithering, cancel it when proteus VSM debug
		int _hr = hour();
		unsigned long previous = millis()-500;
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
		setTime(_hr, 0, 0, 12, 12, 2012);
		while (digitalRead(SET) == LOW);//eliminate dithering, cancel it when proteus VSM debug
	}

}