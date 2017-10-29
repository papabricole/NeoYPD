#pragma once
extern "C" {
#include <os_type.h>
#include <osapi.h>
}

#include <Adafruit_NeoPixel.h>

class LedRing {
public:
    LedRing(uint8_t pin);

    void start();
    void stop();

private:
    Adafruit_NeoPixel strip;
    int counter;
    void run();
    os_timer_t _scheduler;
    static void tickerCallback(LedRing*);
};
