#include "led.h"
#include <fstream>
#include <QDebug>

using namespace std;

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
    string fname1;
    string fname2;
    fname1 = "/sys/class/gpio/gpio";
    fname2 = "/value";
    ifstream fin(fname1 + to_string(pin) +fname2);
    if(fin.fail()){
        throw "file open failed. Please check permission.\n";
    }
    string str;
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
    string fname1;
    string fname2;
    fname1 = "/sys/class/gpio/gpio";
    fname2 = "/value";
    ofstream fout(fname1 + to_string(pin) +fname2);
    if(fout.fail()){
        throw "file open failed. Please check permission.\n";
    }
    fout << to_string(v);
}

void Led::led_event(Led::LedEvent event)
{
    try
    {
        LED_ON == event ? setValue(1) : setValue(0);
    }
    catch(const char* err)
    {
        qWarning() << err;
        exit(EXIT_FAILURE);
    }
}
