#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include "led.h"
#include "switch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setFrameSWStyleSheet(QFrame *f, Switch::SwitchEvent event);
    void checkSWState();

signals:
    void led_event(Led::LedEvent);

private slots:
    void sw1_event(Switch::SwitchEvent event);
    void sw2_event(Switch::SwitchEvent event);
    void sw3_event(Switch::SwitchEvent event);
};

#endif // MAINWINDOW_H
