#include "LedRing.h"
#include <Arduino.h>

LedRing::LedRing(uint8_t pin)
    : strip(12, pin, NEO_GRB + NEO_KHZ800)
{
    strip.begin();

    os_timer_setfn(&_scheduler, reinterpret_cast<os_timer_func_t*>(&LedRing::tickerCallback),
        reinterpret_cast<void*>(this));
}

void LedRing::start()
{
    counter = 0;
    os_timer_arm(&_scheduler, 40, 1);
}

void LedRing::stop()
{
    os_timer_disarm(&_scheduler);

    strip.clear();
    strip.show();
}

void LedRing::run()
{
    const uint32_t WHITE = strip.Color(255, 255, 255);
    const uint32_t RED = strip.Color(255, 0, 0);
    const uint32_t BLUE = strip.Color(0, 0, 255);

    for (int i = 0; i < strip.numPixels(); ++i) {
        const int index = (i + counter) % strip.numPixels();
        strip.setPixelColor(index, (i > strip.numPixels() / 2) ? BLUE : RED);
    }

    const int counter2 = counter / strip.numPixels();
    if (counter % 2 == 0) {
        const int index = (counter2 % 2 == 0) ? 1 : 7;
        strip.setPixelColor(index + 0, WHITE);
        strip.setPixelColor(index + 1, WHITE);
        strip.setPixelColor(index + 2, WHITE);
    }

    strip.show();
    counter++;
}

void LedRing::tickerCallback(LedRing* __thisLedRing)
{
    __thisLedRing->run();
}