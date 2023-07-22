#include "serportsettwin.h"
#include "ui_serportsettwin.h"

SerPortSettWin::SerPortSettWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerPortSettWin)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        ui->comboBox->addItem(serialPortInfo.portName());
        #ifdef DEBUG_APP
        qDebug()<< "SER PORT : " << serialPortInfo.portName() << serialPortInfo.description() << serialPortInfo.manufacturer();
        #endif
    }
}

SerPortSettWin::~SerPortSettWin()
{
    delete ui;
}

void SerPortSettWin::on_pushButton_clicked()
{
    QString tmp = ui->comboBox->currentText();
    if(tmp.isNull()){
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Ignore);
        msg.setStyleSheet("background-color: rgb(53, 53, 53); color: rgb(255, 255, 255);");
        msg.setText("Choose a COM port or insert a serial port and reopen the window!");
        msg.setWindowTitle("Warning");
        int ret = msg.exec();
        if(ret == QMessageBox::Ok){
            return;
        }
        else {
            this->close();
            return;
        }
    }
    COMPortName = ui->comboBox->currentText();
    COMPortParity = ui->comboBox_3->currentText();
    COMPortBaud = ui->comboBox_2->currentText();
    this->close();
}
