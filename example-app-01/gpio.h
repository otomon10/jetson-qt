#ifndef GPIO_H
#define GPIO_H

class Gpio{
public:
    enum Direction {
        OUT,
        IN
    };

    virtual ~Gpio() = 0;
    virtual int getValue() = 0;
    virtual void setValue(int v) = 0;
};

#endif // GPIO_H
