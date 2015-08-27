#include <FastLED.h>

#include "FastLEDProvider.h"
#include "NightwingRegular.h"
#include "Pattern.h"
#include "PatternController.h"
#include "RainbowCycle.h"
#include "TheaterChase.h"

using Controller = PatternController<4, 75, 0>;

class CyclePatterns : public IOnComplete
{
public:
  void OnComplete(IPatternController *ctrl) override {
  	ctrl->nextPattern();
  }
};

PatternPtr patterns[] = {
	new NightwingRegular(1, CRGB::Blue, CRGB::Yellow),
	new NightwingRegular(2, CRGB::Red, CRGB::Cyan),
	new TheaterChase(CRGB::Blue, CRGB::Gold),
	new RainbowCycle()
};

FastLEDProvider<16> leds = {&(FastLED.addLeds<NEOPIXEL, (int)6>)};
Controller controller = Controller { &leds, patterns
	, new CyclePatterns()
};

void setup()
{
	leds.Blackout();
	Serial.begin(115200);
}

void loop()
{
	controller.update();
}