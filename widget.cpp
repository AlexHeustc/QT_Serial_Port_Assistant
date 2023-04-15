#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList serialNameport;

    serialport = new QSerialPort(this);

    //信号绑定到槽
    connect(ui->openBt,&QPushButton::clicked,this,&Widget::openBt);
    connect(ui->sendBt,&QPushButton::clicked,this,&Widget::sendBt);
    connect(ui->closeBt,&QPushButton::clicked,this,&Widget::closeBt);
    connect(ui->clearBt,&QPushButton::clicked,this,&Widget::clearBt);

    connect(serialport,&QSerialPort::readyRead,this,&Widget::serialPortReadyRead_Solt);

    foreach (const QSerialPortInfo& info, QSerialPortInfo::availablePorts()) {
        serialNameport<<info.portName();
    }
    ui->serialCb->addItems(serialNameport);


}
Widget::~Widget()
{
    delete ui;
}


void Widget::openBt()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;


    switch (ui->portrate->currentText().toInt()) {
    case 4800:
        baudRate = QSerialPort::Baud4800;
        break;
    case 9600:
        baudRate = QSerialPort::Baud9600;
        break;
    case 115200:
        baudRate = QSerialPort::Baud115200;
        break;
    default:
        break;
    }

    switch (ui->dataCb->currentText().toInt()) {
    case 5:
        dataBits = QSerialPort::Data5;
        break;
    case 6:
        dataBits = QSerialPort::Data6;
        break;
    case 7:
        dataBits = QSerialPort::Data7;
        break;
    case 8:
        dataBits = QSerialPort::Data8;
        break;
    default:
        break;
    }

    if(ui->stopCb->currentText() == "1"){
        stopBits = QSerialPort::OneStop;
    }else if(ui->stopCb->currentText() == "1.5"){
        stopBits = QSerialPort::OneAndHalfStop;
    }else if(ui->stopCb->currentText() == "2"){
        stopBits = QSerialPort::TwoStop;
    }

    if(ui->checkCb->currentText() == "none"){
        checkBits = QSerialPort::NoParity;
    }

    serialport->setPortName(ui->serialCb->currentText());
    serialport->setBaudRate(baudRate);
    serialport->setDataBits(dataBits);
    serialport->setStopBits(stopBits);
    serialport->setParity(checkBits);

    if(serialport->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"Hint","Serial open sucessed!");
    }else {
        QMessageBox::critical(this,"Hint","Serial open failed!");
    }

}


void Widget::closeBt()
{
    QMessageBox::information(this,"Hint","Close serial successed!");
    serialport->close();
}

void Widget::sendBt()
{
    serialport->write(ui->sendEdit->text().toLocal8Bit().data());
}

void Widget::serialPortReadyRead_Solt(){
    QString buf;
    buf = QString(serialport->readAll());
    ui->receiveEdit->appendPlainText(buf);
}


void Widget::clearBt()
{
    serialport->clear();
    ui->receiveEdit->clear();
}

