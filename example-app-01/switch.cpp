#include "switch.h"
#include <fstream>
#include <QDebug>

using namespace std;

Switch::Switch(int p, Direction d, int v) :
    pin(p),
    dir(d),
    value(v)
{
    // start thread
    start();
}

Switch::~Switch()
{
}

int Switch::getValue()
{
    if(dir == OUT){
        throw "setValue() Failed. Please set direction = IN.\n";
    }
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
    value = atoi(str.c_str());
    return value;
}

void Switch::setValue(int v)
{
    throw "setValue() Failed. Not supported.\n";
}

void Switch::run()
{
    try
    {
        int prev_value = 0;
        while(true){
            getValue();
            if(prev_value == value){
                continue;
            }
            if(1 == value){
                emit switch_event(SW_PUSH);
            } else {
                emit switch_event(SW_RELEASE);
            }
            prev_value = value;
            msleep(50);
        }
    }
    catch(const char* err)
    {
        qWarning() << err;
        exit(EXIT_FAILURE);
    }
 }
