#pragma once

#include <FastLED.h>

#include "LEDProvider.h"

// avr-g++ does not support these functions but still tries to add them
// to the symbol files.
//
// These definitions come from: http://www.avrfreaks.net/comment/341297#comment-341297
__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);}
void __cxa_guard_release (__guard *g) {*(char *)g = 1;}
void __cxa_guard_abort (__guard *) {}

template<int NUM_PIXELS>
class FastLEDProvider : public ILEDProvider
{
public:
	FastLEDProvider(CLEDController &(*addLeds)(struct CRGB *data, int nLedsOrOffset, int nLedsIfOffset))
	{
		addLeds(leds, NUM_PIXELS, 0);
	}

	~FastLEDProvider()
	{

	}

	void SetPixelColor(int idx, uint8_t red, uint8_t green, uint8_t blue) override
	{
		if (idx >= NUM_PIXELS)
		{
			return;
		}
		leds[idx].red = red;
		leds[idx].green = green;
		leds[idx].blue = blue;
	}

	void SetPixelColor(int idx, uint32_t color) override
	{
		if (idx >= NUM_PIXELS)
		{
			return;
		}
		leds[idx] = color;		
	}

	void Show() override
	{
		FastLED.show();
	}

	void Blackout() override
	{
		memset(leds, 0, sizeof(leds));
		FastLED.show();
	};

	int PixelCount() const override
	{
		return NUM_PIXELS;
	}

private:
	CRGB leds[NUM_PIXELS];
};