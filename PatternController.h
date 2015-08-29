#pragma once

#include "Pattern.h"
#include "LEDProvider.h"

enum class Direction {
	Forward,
	Reverse
};

class IPatternController
{
public:
	int interval;
	Direction direction;

	IPatternController(int i, Direction d)
	  : interval(i)
	  , direction(d)
	{
	}

	virtual void nextPattern() = 0;
	virtual void setPattern(int patternIdx) = 0;
	virtual PatternPtr getCurrentPattern() = 0;
};

class IOnComplete {
public:
	virtual void OnComplete(IPatternController *) = 0;
};
using OnCompletePtr=IOnComplete*;



template<int NUM_PATTERNS, int DEFAULT_INTERVAL, int START_PATTERN>
class PatternController : public IPatternController
{
public:
	PatternController(LEDProviderPtr provider, PatternPtr in_patterns[NUM_PATTERNS], OnCompletePtr callback=nullptr)
	  : IPatternController(DEFAULT_INTERVAL, Direction::Forward)
      , currentPatternIndex(START_PATTERN)
      , lastUpdate(0)
      , index(0)
	  , patterns(in_patterns)
      , currentPattern(nullptr)
      , onComplete(callback)
      , provider(provider)
    {
    	setPattern(START_PATTERN);
    	for(int i=0; i<NUM_PATTERNS; i++) {
    		patterns[i]->SetPixelCount(provider->PixelCount());
    	}
    }

	~PatternController() = default;

	bool update()
	{
		if (millis() - lastUpdate > interval) {
			lastUpdate = millis();
			
			if (currentPattern) { // Deal with nullptrs
				currentPattern->update(index, provider);
			}
			increment();

			return true;
		}

		return false;
	}

	void increment() {
		if (direction == Direction::Forward)
		{
			index += 1;
			if (index >= currentPattern->totalSteps())
			{
				index = 0;
				OnCompleteCallback();
			}
		} else {
			index -= 1;
			if (index < 0) {
				index = currentPattern->totalSteps() -1;
				OnCompleteCallback();
			}
		}
	}

	void nextPattern() override {
		currentPatternIndex = (currentPatternIndex + 1) % NUM_PATTERNS;
		currentPattern = patterns[currentPatternIndex];
	}

	void setPattern(int patternIdx) override {
		currentPatternIndex = patternIdx % NUM_PATTERNS;
		currentPattern = patterns[currentPatternIndex];
	}

	PatternPtr getCurrentPattern() override {
		return currentPattern;
	}

	void OnCompleteCallback() {
		if (onComplete) {
			Serial.println("onComplete called");
			onComplete->OnComplete(this);
		}
	}

private:
	int currentPatternIndex;
	float lastUpdate;
	int index;
	PatternPtr *patterns;
	PatternPtr currentPattern;
	OnCompletePtr onComplete;
	LEDProviderPtr provider;
};