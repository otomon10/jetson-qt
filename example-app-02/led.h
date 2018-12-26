#ifndef LED_H
#define LED_H

#include "gpio.h"

class Led : public Gpio{
public:
    enum LedEvent{
        LED_ON,
        LED_OFF
    };
    explicit Led(int p, Direction d);
    ~Led();
    int getValue();
    void setValue(int d);

//private slots:
    //void led_event(Led::LedEvent event);    // Need Led:: for MetaType
    void led_event(LedEvent event);

private:
    int pin;
    int dir;
};

#endif // LED_H
