#pragma once
extern "C" {
#include <os_type.h>
#include <osapi.h>
}

class Siren {
public:
    Siren(uint8_t pin);
    enum Type { WAIL = 100, YELP = 10, PIER = 2 };
    void start(Type type);
    void stop();

private:
    uint8_t buzzerPin;
    int time, speed;
    void run();
    os_timer_t _scheduler;
    static void tickerCallback(Siren*);
};
