#ifndef SWITCH_H
#define SWITCH_H

#include <QThread>
#include "gpio.h"

class Switch : public QThread, public Gpio {
    Q_OBJECT

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

private:
    int pin;
    int dir;
    int value;

protected:
    void run();

signals:
    void switch_event(Switch::SwitchEvent event);   // Need Led:: for MetaType
};

#endif // SWITCH_H
