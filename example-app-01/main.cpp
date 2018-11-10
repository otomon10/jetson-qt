#include "mainwindow.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    Switch *sw1 = new Switch(63, Gpio::IN);
    Switch *sw2 = new Switch(186, Gpio::IN);
    Switch *sw3 = new Switch(219, Gpio::IN);
    Led *led = new Led(511, Gpio::OUT);
    QThread* th_led = new QThread;

    // thread settings
    led->moveToThread(th_led);
    th_led->start();

    // set signals param
    qRegisterMetaType<Switch::SwitchEvent>("Switch::SwitchEvent");
    qRegisterMetaType<Led::LedEvent>("Led::LedEvent");

    // To UI
    QObject::connect(sw1, SIGNAL(switch_event(Switch::SwitchEvent)), w, SLOT(sw1_event(Switch::SwitchEvent)));
    QObject::connect(sw2, SIGNAL(switch_event(Switch::SwitchEvent)), w, SLOT(sw2_event(Switch::SwitchEvent)));
    QObject::connect(sw3, SIGNAL(switch_event(Switch::SwitchEvent)), w, SLOT(sw3_event(Switch::SwitchEvent)));
    // From UI
    QObject::connect(w, SIGNAL(led_event(Led::LedEvent)), led, SLOT(led_event(Led::LedEvent)));

    w->show();

    return a.exec();
}
