#include <Time.h>
#include <TimeLib.h>
#include "BinaryClock.h"
void setup()
{
	BinaryClock_Port();
}

void loop()
{
	BinaryClock_Set();
	BinaryClock_Hour(hourFormat12());
	BinaryClock_Minute(minute());
	BinaryClock_Seconds(second());
}
