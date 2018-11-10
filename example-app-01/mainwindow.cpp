#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::checkSWState()
{
    if(ui->frame_sw1->styleSheet() == "background-color:Green" ||
       ui->frame_sw2->styleSheet() == "background-color:Green" ||
       ui->frame_sw3->styleSheet() == "background-color:Green" ){
       qDebug() << "LED ON";
       emit led_event(Led::LedEvent::LED_ON);
    } else {
       qDebug() << "LED OFF";
       emit led_event(Led::LedEvent::LED_OFF);
    }
}

void MainWindow::sw1_event(Switch::SwitchEvent event)
{
    setFrameSWStyleSheet(ui->frame_sw1, event);
    checkSWState();
}

void MainWindow::sw2_event(Switch::SwitchEvent event)
{
    setFrameSWStyleSheet(ui->frame_sw2, event);
    checkSWState();
}

void MainWindow::sw3_event(Switch::SwitchEvent event)
{
    setFrameSWStyleSheet(ui->frame_sw3, event);
    checkSWState();
}
