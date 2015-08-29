#include <FastLED.h>
#include <CapacitiveSensor.h>

#include "Blackout.h"
#include "FastLEDProvider.h"
#include "NightwingRegular.h"
#include "Pattern.h"
#include "PatternController.h"
#include "RainbowCycle.h"
#include "TheaterChase.h"

#define DEFAULT_INTERVAL 75
#define MODE_SENSOR_SEND 2
#define MODE_SENSOR_RECV 4
#define SENSOR_THRESHOLD 400
#define TRIGGER_THRESHOLD 5000

unsigned long csSum = 0;
bool triggered = false;

using Controller = PatternController<5, DEFAULT_INTERVAL, 0>;
CapacitiveSensor mode_select = CapacitiveSensor(MODE_SENSOR_SEND, MODE_SENSOR_RECV);

class CyclePatterns : public IOnComplete
{
public:
  void OnComplete(IPatternController *ctrl) override {
  	switch(ctrl->getCurrentPattern()->id()) {
  		case PatternIds::Blackout:
  			ctrl->interval = 500;
  			break;
  		default:
  			ctrl->interval = DEFAULT_INTERVAL;
  			break;
  	}
  }
};

PatternPtr patterns[] = {
	new NightwingRegular(1, CRGB::Blue, CRGB::Yellow),
	new NightwingRegular(2, CRGB::Red, CRGB::Cyan),
	new TheaterChase(CRGB::Blue, CRGB::Gold),
	new RainbowCycle(),
	new Blackout()
};

FastLEDProvider<8> leds = {&(FastLED.addLeds<NEOPIXEL, (int)6>)};
Controller controller = Controller { &leds, patterns
	// , new CyclePatterns()
};

inline bool update()
{
	return controller.update();
}

inline void onButtonDown() {
	controller.nextPattern();
}

inline void readSensor()
{
	long value = mode_select.capacitiveSensor(30);

	if (value > SENSOR_THRESHOLD )
	{
		Serial.print(value);
		Serial.print(" ");
		Serial.println(csSum);
		csSum += value;
		if (csSum >= TRIGGER_THRESHOLD && !triggered) {
			onButtonDown();
			triggered = true;
		}
	} else {
		csSum = 0;
		triggered = false;
	}	
}


void setup()
{
	leds.Blackout();
	Serial.begin(115200);
}

void loop()
{
	if (update()) {
		readSensor();
	}
}