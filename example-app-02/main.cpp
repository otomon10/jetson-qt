#include "mainwindow.h"
#include <QApplication>
//#include <QThread>
#include <thread>
#include <boost/signals2/signal.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    Switch *sw1 = new Switch(63, Gpio::IN);
    Switch *sw2 = new Switch(186, Gpio::IN);
    Switch *sw3 = new Switch(219, Gpio::IN);
    Led *led = new Led(511, Gpio::OUT);

    //QThread* th_led = new QThread;
    //led->moveToThread(th_led);
    //th_led->start();

    // thread settings(std::Thread)
    std::thread th_sw1(&Switch::run, sw1);
    std::thread th_sw2(&Switch::run, sw2);
    std::thread th_sw3(&Switch::run, sw3);

    // set signals param
    //qRegisterMetaType<Switch::SwitchEvent>("Switch::SwitchEvent");
    //qRegisterMetaType<Led::LedEvent>("Led::LedEvent");

    // To UI
    //QObject::connect(sw1, SIGNAL(switch_event(Switch::SwitchEvent)), w, SLOT(sw1_event(Switch::SwitchEvent)));
    //QObject::connect(sw2, SIGNAL(switch_event(Switch::SwitchEvent)), w, SLOT(sw2_event(Switch::SwitchEvent)));
    //QObject::connect(sw3, SIGNAL(switch_event(Switch::SwitchEvent)), w, SLOT(sw3_event(Switch::SwitchEvent)));
    sw1->switch_event.connect(boost::bind(&MainWindow::sw1_event, w, _1));
    sw2->switch_event.connect(boost::bind(&MainWindow::sw2_event, w, _1));
    sw3->switch_event.connect(boost::bind(&MainWindow::sw3_event, w, _1));

    // From UI
    //QObject::connect(w, SIGNAL(led_event(Led::LedEvent)), led, SLOT(led_event(Led::LedEvent)));
    QObject::connect(w, &MainWindow::led_event, [=](Led::LedEvent event){led->led_event(event);});

    w->show();

    /// TODO
    /// - confirm thread addr
    /// - make led and switch shared object

    return a.exec();
}
