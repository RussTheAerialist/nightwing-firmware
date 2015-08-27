#pragma once

uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
}

uint32_t Color(byte r, byte g, byte b)
{
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85)
    {
        return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else if(WheelPos < 170)
    {
        WheelPos -= 85;
        return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

uint32_t DarkenColor(uint32_t color) {
    return Color(
        Red(color) >> 1,
        Green(color) >> 1,
        Blue(color) >> 1
    );
}

uint32_t LightenColor(uint32_t color) {
    return Color(
        (Red(color) << 1)&255,
        (Green(color) << 1)&255,
        (Blue(color) << 1)&255
    );
}