#pragma once

#include <conio.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>

#include "../sge_defines.h"






void WaitKey(char k = 0)
{

	int c = _getch();
	if (k != 0 && k != c)
		WaitKey(k);
}

void Pause(unsigned int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


// Adapted from: http://stackoverflow.com/a/2667344/2277490
// credit to: Rahul Naik

// also check this out: https://github.com/miloyip/dtoa-benchmark
#define PRECISION 7
char* FloatToString(char* buffer, u32 n, float num)
{
	int whole_part = (int)num;
	int digit = 0, reminder = 0;
	int log_value = (int)log10(num), index = log_value;
	long wt = 0;

	// String containg result
	char* str = buffer; // new char[20];

						//Initilise string to zero
	memset(str, 0, n);

	// HACK: blows up if num = 0.0f
	if (num == 0.0f) {
		buffer[0] = '0';
		buffer[1] = '.';
		buffer[2] = '0';
		return str;
	}

	//Extract the whole part from float num
	for (float i = 1; i < log_value + 2; i++)
	{
		wt = (int)powf(10.0, i);
		reminder = whole_part % wt;
		digit = (reminder - digit) / (wt / 10);

		//Store digit in string
		str[index--] = digit + 48;              // ASCII value of digit  = digit + 48
		if (index == -1)
			break;
	}

	index = log_value + 1;
	str[index] = '.';

	float fraction_part = num - whole_part;
	float tmp1 = fraction_part, tmp = 0;

	//Extract the fraction part from  num
	for (int i = 1; i < PRECISION; i++)
	{
		wt = 10;
		tmp = tmp1 * wt;
		digit = (int)tmp;

		//Store digit in string
		str[++index] = digit + 48;           // ASCII value of digit  = digit + 48
		tmp1 = tmp - digit;
	}

	return str;
}

// Andreas Bonini http://stackoverflow.com/a/1861337/2277490
u64 GetTimeMilli64()
{
#ifdef _WIN32
	/* Windows */
	FILETIME ft;
	LARGE_INTEGER li;

	/* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
	* to a LARGE_INTEGER structure. */
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;

	u64 ret = li.QuadPart;
	ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
	ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

	return ret;
#else
	/* Linux */
	struct timeval tv;

	gettimeofday(&tv, NULL);

	/* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
	ret /= 1000;

	/* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
	ret += (tv.tv_sec * 1000);

	return ret;
#endif
}

u64 GetTimeMicro64()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


bool StringToNumber(float& f, char* str)
{
	char* p(0);
	float retf = static_cast<float>(strtod(str, &p));
	if (*p)
		return false;
	f = retf;
	return true;
}

bool StringToNumber(double& f, char* str)
{
	char* p(0);
	double retf = strtod(str, &p);
	if (*p)
		return false;
	f = retf;
	return true;
}

bool StringToNumber(u32& u, char* str)
{
	char* p(0);
	u = static_cast<u32>(strtoul(str, &p, 0));
	if (*p)
		return false;
	return true;
}

bool StringToNumber(u64& u, char* str)
{
	char* p(0);
	u = strtoul(str, &p, 0);
	if (*p)
		return false;
	return true;
}

bool StringToNumber(i32 u, char* str)
{
	char* p(0);
	u = static_cast<u32>(strtol(str, &p, 10));
	if (*p)
		return false;
	return true;
}

bool StringToNumber(i64 u, char* str)
{
	char* p(0);
	u = strtoul(str, &p, 10);
	if (*p)
		return false;
	return true;
}



