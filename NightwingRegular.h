#pragma once

// Based on https://learn.adafruit.com/multi-tasking-the-arduino-part-3/recycling-the-rainbow
// but adapted to my own PatternController and using the generic provider

#include "Pattern.h"
#include "PatternIds.h"
#include "LEDProvider.h"
#include "utils.h"

class NightwingRegular : public Pattern
{
public:
	NightwingRegular(int shockProbability, uint32_t color1, uint32_t color2)
	  : color1(color1)
	  , color2(color2)
      , shockProbability(shockProbability)
    {

	}
	void update(int idx, LEDProviderPtr leds) override
	{
        for(int i=0; i< pixelCount; i++)
        {
            int rValue = random(100);
            Serial.println(rValue);
            if (rValue < shockProbability) {
                leds->SetPixelColor(i, color2);
            } else {
                switch(random(3)) {
                    case 1:
                      leds->SetPixelColor(i, DarkenColor(color1));
                      break;

                    case 2:
                      leds->SetPixelColor(i, LightenColor(color1));
                      break;

                    default:
                      leds->SetPixelColor(i, color1);
                      break;

                }
            }
        }

		leds->Show();
	}

	int totalSteps() const override { return pixelCount * 10; }
    PatternIds id() const override { return PatternIds::NightwingRegular; }

private:
	uint32_t color1, color2;
    int shockProbability;
};