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
	BinaryClock_Set();
	BinaryClock_Hour(hour());
	BinaryClock_Minute(minute());
	BinaryClock_Seconds(second());
}
