#ifndef ADDDEVWIN_H
#define ADDDEVWIN_H

#include <QDialog>
#include "shareddata.h"
#include "databasethread.h"
#include <QFileDialog>

namespace Ui {
class AddDevWin;
}

class AddDevWin : public QDialog
{
    Q_OBJECT

public:
    explicit AddDevWin(QWidget *parent = nullptr);
    ~AddDevWin();
    int res = 0;
    QString devName = "DEVICE-#";
    int devAdd = 1;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::AddDevWin *ui;
    DataBaseThread *dbThread;
    QString pathDb = QDir::currentPath();
    QString fileO;
};

#endif // ADDDEVWIN_H
