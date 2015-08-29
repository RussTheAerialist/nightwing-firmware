#pragma once

// Based on https://learn.adafruit.com/multi-tasking-the-arduino-part-3/recycling-the-rainbow
// but adapted to my own PatternController and using the generic provider

#include "Pattern.h"
#include "PatternIds.h"
#include "LEDProvider.h"
#include "utils.h"

class Blackout : public Pattern
{
public:
	void update(int idx, LEDProviderPtr leds) override
	{
		leds->Blackout();
	}

	int totalSteps() const override { return 1; }
	PatternIds id() const override { return PatternIds::Blackout; }
};
