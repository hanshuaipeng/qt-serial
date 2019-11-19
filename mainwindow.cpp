#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCanBus>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    ui->BaudBox->setCurrentIndex(3);
    ui->sendButton->setEnabled(false);
    this->resize(1024,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_sendButton_clicked()
{
    serial->write(ui->textEdit_2->toPlainText().toLatin1());
}

void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text() == "open")
    {
        serial = new QSerialPort;
        serial->setPortName(ui->PortBox->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        ui->sendButton->setEnabled(true);
        ui->openButton->setText("close");
        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::Read_Data);
    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
        ui->openButton->setText("open");
    }
}

void MainWindow::Read_Data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        QString str = ui->textEdit->toPlainText();
        str += tr(buf);
        ui->textEdit->clear();
        ui->textEdit->append(str);
    }
    buf.clear();
}
