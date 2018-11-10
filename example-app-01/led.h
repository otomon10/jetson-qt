#ifndef LED_H
#define LED_H

#include <QObject>
#include "gpio.h"

class Led : public QObject, public Gpio{
    Q_OBJECT

public:
    enum LedEvent{
        LED_ON,
        LED_OFF
    };
    explicit Led(int p, Direction d);
    ~Led();
    int getValue();
    void setValue(int d);

private:
    int pin;
    int dir;

private slots:
    void led_event(Led::LedEvent event);    // Need Led:: for MetaType
};

#endif // LED_H
