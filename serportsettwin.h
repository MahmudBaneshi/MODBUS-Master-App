#ifndef SERPORTSETTWIN_H
#define SERPORTSETTWIN_H

#include <QDialog>
#include "shareddata.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class SerPortSettWin;
}

class SerPortSettWin : public QDialog
{
    Q_OBJECT

public:
    explicit SerPortSettWin(QWidget *parent = nullptr);
    ~SerPortSettWin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SerPortSettWin *ui;
};

#endif // SERPORTSETTWIN_H
