#pragma once

// Based on https://learn.adafruit.com/multi-tasking-the-arduino-part-3/recycling-the-rainbow
// but adapted to my own PatternController and using the generic provider

#include "Pattern.h"
#include "PatternIds.h"
#include "LEDProvider.h"
#include "utils.h"

class TheaterChase : public Pattern
{
public:
	TheaterChase(uint32_t color1, uint32_t color2)
	  : color1(color1)
	  , color2(color2)
    {

	}
	void update(int idx, LEDProviderPtr leds) override
	{
        for(int i=0; i< pixelCount; i++)
        {
            if ((i + idx) % 3 == 0)
            {
                leds->SetPixelColor(i, color1);
            }
            else
            {
                leds->SetPixelColor(i, color2);
            }
        }

		leds->Show();
	}

	int totalSteps() const override { return pixelCount * 10; }
	PatternIds id() const override { return PatternIds::TheaterChase; }

private:
	uint32_t color1, color2;
};