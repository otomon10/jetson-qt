#include "led.h"
#include <iostream>
#include <fstream>

Led::Led(int p, Direction d) :
    pin(p),
    dir(d)
{
}

Led::~Led()
{
}

int Led::getValue()
{
    std::string fname1;
    std::string fname2;
    fname1 = "/sys/class/gpio/gpio";
    fname2 = "/value";
    std::ifstream fin(fname1 + std::to_string(pin) +fname2);
    if(fin.fail()){
        throw "file open failed. Please check permission.\n";
    }
    std::string str;
    fin >> str;
    return atoi(str.c_str());
}

void Led::setValue(int v)
{
    if(dir == IN){
        throw "setValue() Failed. Please set direction = OUT.\n";
    }
    if(v == getValue()){
        return;
    }
    std::string fname1;
    std::string fname2;
    fname1 = "/sys/class/gpio/gpio";
    fname2 = "/value";
    std::ofstream fout(fname1 + std::to_string(pin) +fname2);
    if(fout.fail()){
        throw "file open failed. Please check permission.\n";
    }
    fout << std::to_string(v);
}

void Led::led_event(Led::LedEvent event)
{
    try
    {
        LED_ON == event ? setValue(1) : setValue(0);
    }
    catch(const char* err)
    {
        std::cerr << err;
        exit(EXIT_FAILURE);
    }
}
