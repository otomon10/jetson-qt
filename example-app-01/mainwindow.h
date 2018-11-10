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
    Led *led;
    Switch *sw1;
    Switch *sw2;
    Switch *sw3;
    void setFrameSWStyleSheet(QFrame *f, Switch::SwitchEvent event);

private slots:
    void on_pushButton_clicked();
    void sw1_event(Switch::SwitchEvent event);
    void sw2_event(Switch::SwitchEvent event);
    void sw3_event(Switch::SwitchEvent event);
};

#endif // MAINWINDOW_H
