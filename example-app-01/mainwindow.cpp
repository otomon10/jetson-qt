#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    led(new Led(511, Gpio::OUT)),
    sw1(new Switch(63, Gpio::IN)),
    sw2(new Switch(186, Gpio::IN)),
    sw3(new Switch(219, Gpio::IN))
{
    ui->setupUi(this);

    // set signals param
    qRegisterMetaType<Switch::SwitchEvent>("Switch::SwitchEvent");
    connect(sw1, SIGNAL(switch_event(Switch::SwitchEvent)), this, SLOT(sw1_event(Switch::SwitchEvent)));
    connect(sw2, SIGNAL(switch_event(Switch::SwitchEvent)), this, SLOT(sw2_event(Switch::SwitchEvent)));
    connect(sw3, SIGNAL(switch_event(Switch::SwitchEvent)), this, SLOT(sw3_event(Switch::SwitchEvent)));

    // start thread
    sw1->start();
    sw2->start();
    sw3->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete led;
    delete sw1;
    delete sw2;
    delete sw3;
}

void MainWindow::on_pushButton_clicked()
{
    led->state() ? led->off() : led->on();
}

void MainWindow::setFrameSWStyleSheet(QFrame *f, Switch::SwitchEvent event)
{
    if(Switch::SW_PUSH == event){
        qDebug() << f->objectName() + " pushed";
        f->setStyleSheet("background-color:Green");
    }
    else if (Switch::SW_RELEASE == event){
        qDebug() << f->objectName() + " released";
        f->setStyleSheet("background-color:None");
    }
}

void MainWindow::sw1_event(Switch::SwitchEvent event)
{
    setFrameSWStyleSheet(ui->frame_sw1, event);
}

void MainWindow::sw2_event(Switch::SwitchEvent event)
{
    setFrameSWStyleSheet(ui->frame_sw2, event);
}

void MainWindow::sw3_event(Switch::SwitchEvent event)
{
    setFrameSWStyleSheet(ui->frame_sw3, event);
}
