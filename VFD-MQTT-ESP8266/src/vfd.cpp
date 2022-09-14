// Copyright (c) 2022 Esteban Cadic
// This code is licensed under MIT license (see LICENSE file for details)

#include <Arduino.h>
#include "vfd.h"

#define EPSON_INIT          "\x1B\x40"
#define EPSON_CLEAR         "\x0C"
#define EPSON_BLINK         "\x1F\x45" // Add delay (n) after (0 <= n <= 255) (n*50 ms)
#define EPSON_CODEPAGE_1252 "\x1B\x74\x10"
#define EPSON_H_SCROLL      "\x1F\x03"
#define EPSON_V_SCROLL      "\x1F\x02"
#define EPSON_TIME          "\x1F\x54" // Add hour (h) and minute (m) after (0 <= h <= 23) (0 <= 59)
#define EPSON_CURSOR        "\x1F\x43"

#define ASCII_TO_HEX(c) ((c <= '9') ? (c - '0') : (c - 'A' + 10))

void vfdSetup(void)
{
	Serial1.begin(115200);

	Serial1.write(EPSON_INIT);
	Serial1.write(EPSON_CODEPAGE_1252);

	Serial1.write(EPSON_CURSOR);
	Serial1.write(0); // Cursor off

	Serial1.print("    Discord VFD    \n\r");
	Serial1.print(" github.com/Estylos");
}

void vfdWrite(unsigned char c)
{
	static bool percentEncoding = false;
	static bool firstDigit = false;
	static unsigned char code = 0;

	// Part for Windows-1252 character percent-encoding
	if (c == '%')
	{
		percentEncoding = true; // An percent encoded character will be processed
	}
	else if (percentEncoding == true && firstDigit == false) // First digit of the % code
	{
		code = (ASCII_TO_HEX(c) << 4);
		firstDigit = true;

	}
	else if (percentEncoding == true && firstDigit == true) // Fulled code
	{
		code |= ASCII_TO_HEX(c);

		percentEncoding = false;

		Serial1.write(code);

		firstDigit = false;
	}
	else
	{
		Serial1.write(c);
	}
}

void vfdClear(void)
{
	Serial1.write(EPSON_CLEAR);
}
