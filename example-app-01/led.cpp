#include "led.h"
#include <fstream>

using namespace std;

Led::Led(int p, Direction d){
    pin = p;
    dir = d;
    value = 0;
}
Led::~Led(void){
}
int Led::getValue(){
    string fname1;
    string fname2;
    fname1 = "/sys/class/gpio/gpio";
    fname2 = "/value";
    ifstream fin(fname1 + to_string(pin) +fname2);
    if(fin.fail()){
        throw "fin failed.\n";
    }
    string str;
    fin >> str;
    value = atoi(str.c_str());
    return value;
}
void Led::setValue(int v){
    if(dir == IN){
        throw "setValue() Failed. Please set direction = OUT.\n";
    }
    string fname1;
    string fname2;
    fname1 = "/sys/class/gpio/gpio";
    fname2 = "/value";
    ofstream fout(fname1 + to_string(pin) +fname2);
    if(fout.fail()){
        throw "fout failed.\n";
    }
    fout << to_string(v);
    value = v;
}
void Led::on(){
    setValue(1);
}
void Led::off(){
    setValue(0);
}
int Led::state(){
    return getValue();
}
