#pragma once

class ILEDProvider;
enum class PatternIds;
using LEDProviderPtr = ILEDProvider*;

class Pattern {
public:
	void SetPixelCount(int count) {
		pixelCount = count;
	}
	virtual void update(int, LEDProviderPtr) = 0;
	virtual int totalSteps() const = 0;
	virtual PatternIds id() const = 0;
protected:
	int pixelCount;
};

using PatternPtr = Pattern*;