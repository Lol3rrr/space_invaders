#ifndef UTILS_H
#define UTILS_H

#include <rtc.h>

void sleepTicks(int ticks);


void sleepTicks(int ticks) {
	int RTC = RTC_GetTicks();
	int dRTC = 0;
	do {
		dRTC = RTC_GetTicks() - RTC;
	}while(dRTC < ticks);
}

#endif