#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <string>
#include <iostream>
#include<QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QSerialPort* serialport;

    ~Widget();

private slots:
    void openBt();

    void closeBt();

    void sendBt();

    void clearBt();

    void serialPortReadyRead_Solt();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
