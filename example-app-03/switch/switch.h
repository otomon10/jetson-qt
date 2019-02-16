#ifndef SWITCH_H
#define SWITCH_H

#include <boost/signals2/signal.hpp>
#include "gpio.h"

class Switch :  public Gpio {

public:
    enum SwitchEvent{
        SW_PUSH,
        SW_RELEASE,
        SW_LONG_PUSH,
    };
    explicit Switch(int p, Direction d, int v = 0);
    ~Switch();
    int getValue();
    void setValue(int d);
    void run();

//signals:
    //void switch_event(Switch::SwitchEvent event);   // Need Switch:: for MetaType
    boost::signals2::signal<void(SwitchEvent)> switch_event;

private:
    int pin;
    int dir;
    int value;
};

#endif // SWITCH_H
