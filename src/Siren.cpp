#include "Siren.h"
#include <Arduino.h>

Siren::Siren(uint8_t pin)
    : buzzerPin(pin)
    , time(0)
    , speed(WAIL)
{
    os_timer_setfn(&_scheduler, reinterpret_cast<os_timer_func_t*>(&Siren::tickerCallback),
        reinterpret_cast<void*>(this));
}

void Siren::start(Siren::Type type)
{
    time = 0;
    speed = int(type);
    os_timer_arm(&_scheduler, 1, 1);
}

void Siren::stop()
{
    os_timer_disarm(&_scheduler);

    analogWrite(buzzerPin, 0);
}

const short rumble[26] = { 818, 1076, 1194, 1287, 1314, 1343, 1372, 1416, 1447, 1478, 1543, 1593,
    1463, 1357, 1233, 1169, 1096, 1039, 975, 934, 895, 866, 848, 804, 779, 746 };

void Siren::run()
{
    const int ia = time / float(speed);
    const int ib = ia + 1;
    const int ta = ia * speed;
    const int fa = rumble[ia % 26];
    const int fb = rumble[ib % 26];

    const int freq = fa + (fb - fa) * ((time - ta) / float(speed));
    analogWriteFreq(freq);
    analogWrite(buzzerPin, 256);

    time += 1;
}

void Siren::tickerCallback(Siren* __this)
{
    __this->run();
}