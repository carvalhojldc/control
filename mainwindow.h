#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "qthread.h"
#include "qcustomplot.h"
#include "control.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void UI_configGraphWrite();

    void UI_configGraphRead();


    void UI_configPanel();

    int UI_getTipoMalha();

    void UI_configCanais();

    void UI_configSignal();

    void UI_malhaFechada();

    void UI_malhaAberta();

    void UI_configMalha();

    void UI_configControlador();

    void UI_limitRandInput();



    void connectServer();

    void stopAll();

    void controladorPID();

    void data();

    void sendData();

    void receiveData();


private:
    Ui::MainWindow *ui;

    Control *control;

    QTimer *timerEscrita;
    QTimer *timerLeitura;

    QThread *threadEscrita;
    QThread *threadLeitura;

    bool canalLeituraVec[NUMB_CAN_READ];
    int canalEscrita = 0;

};

#endif // MAINWINDOW_H
