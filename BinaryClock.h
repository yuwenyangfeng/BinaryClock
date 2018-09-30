
#ifndef BinaryClock_h
#define BinaryClock_h
#include <Arduino.h>
// LED_pin <--->Arduino_pin
enum PIN
{
	H8 = 0, H4, H2, H1, // hour
	M32, M16, M8, M4, M2, M1, // minute
	S32, S16, S8, S4, S2, S1 = 15, // seconds
	SET, ADD
};

// initial ports output
void BinaryClock_Port();
// method
void BinaryClock_Set();
void BinaryClock_Hour(int Hr);
void BinaryClock_Minute(int Min);
void BinaryClock_Seconds(int Sec);
#endif
