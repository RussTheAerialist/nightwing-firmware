#pragma once

class ILEDProvider
{
public:
	virtual void SetPixelColor(int idx, uint8_t red, uint8_t green, uint8_t blue) = 0;
	virtual void SetPixelColor(int idx, uint32_t color) = 0;
	virtual void Show() = 0;
	virtual void Blackout() = 0;
	virtual int PixelCount() const = 0;
};

using LEDProviderPtr = ILEDProvider*;