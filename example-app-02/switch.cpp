#include <iostream>
#include <fstream>
#include <unistd.h>
#include "switch.h"

Switch::Switch(int p, Direction d, int v) :
    pin(p),
    dir(d),
    value(v)
{
}

Switch::~Switch()
{
}

int Switch::getValue()
{
    if(dir == OUT){
        throw "setValue() Failed. Please set direction = IN.\n";
    }
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
    value = atoi(str.c_str());
    return value;
}

void Switch::setValue(int v)
{
    throw "setValue() Failed. Not supported.\n";
}

void Switch::run()
{
    while(1){
        try
        {
            int prev_value = 0;
            while(true){
                getValue();
                if(prev_value == value){
                    continue;
                }
                if(1 == value){
                    //emit switch_event(SW_PUSH);
                    switch_event(SW_PUSH);

                } else {
                    //emit switch_event(SW_RELEASE);
                    switch_event(SW_RELEASE);
                }
                prev_value = value;
                usleep(50 * 1000);
            }
        }
        catch(const char* err)
        {
            std::cerr << err;
            exit(EXIT_FAILURE);
        }
    }
 }
