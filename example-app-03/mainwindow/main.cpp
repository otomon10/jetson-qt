#include "mainwindow.h"
#include <QApplication>
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

    // thread settings(std::Thread)
    std::thread th_sw1(&Switch::run, sw1);
    std::thread th_sw2(&Switch::run, sw2);
    std::thread th_sw3(&Switch::run, sw3);
    th_sw1.detach();
    th_sw2.detach();
    th_sw3.detach();

    // To UI
    sw1->switch_event.connect(boost::bind(&MainWindow::sw1_event, w, _1));
    sw2->switch_event.connect(boost::bind(&MainWindow::sw2_event, w, _1));
    sw3->switch_event.connect(boost::bind(&MainWindow::sw3_event, w, _1));

    // From UI
    QObject::connect(w, &MainWindow::led_event, [=](Led::LedEvent event){
        std::thread th_led(&Led::led_event, led, event);
        th_led.detach();
    });

    w->show();

    return a.exec();
}
