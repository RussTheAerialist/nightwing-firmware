#pragma once

// Based on https://learn.adafruit.com/multi-tasking-the-arduino-part-3/recycling-the-rainbow
// but adapted to my own PatternController and using the generic provider

#include "Pattern.h"
#include "PatternIds.h"
#include "LEDProvider.h"
#include "utils.h"

class RainbowCycle : public Pattern
{
public:
	void update(int idx, LEDProviderPtr leds) override
	{
		for(int i=0; i<leds->PixelCount(); i++) {
			uint32_t color = Wheel(
				(
					(i * 256 / leds->PixelCount()) + idx
				) & 255
			);
			leds->SetPixelColor(i, color);
		}

		leds->Show();
	}

	int totalSteps() const override { return 255; }
	PatternIds id() const override { return PatternIds::RainbowCycle; }
};