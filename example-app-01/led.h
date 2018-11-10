#ifndef LED_H
#define LED_H

#include "gpio.h"

class Led : public Gpio{
private:
    int pin;
    int dir;
    int value;
public:
    explicit Led(int p, Direction d);
    ~Led(void);
    int getValue();
    void setValue(int d);
    void on();
    void off();
    int state();
};

#endif // LED_H
