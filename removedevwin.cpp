#include "removedevwin.h"
#include "ui_removedevwin.h"

RemoveDevWin::RemoveDevWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveDevWin)
{
    ui->setupUi(this);
}

RemoveDevWin::~RemoveDevWin()
{
    delete ui;
}
