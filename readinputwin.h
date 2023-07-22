#ifndef READINPUTWIN_H
#define READINPUTWIN_H

#include <QDialog>
#include "databasethread.h"
#include "noteditabledelegate.h"
#include "spinboxdelegate.h"
#include "lineeditdelegate.h"

namespace Ui {
class ReadInputWin;
}

class ReadInputWin : public QDialog
{
    Q_OBJECT

public:
    explicit ReadInputWin(QWidget *parent = nullptr);
    ~ReadInputWin();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ReadInputWin *ui;
    void updateModel(int first);
    DataBaseThread *dbThread;
    QSqlTableModel *readInTable;
    NotEditableDelegate *noEditDelegate;
    SpinBoxDelegate *spinDelegate;
    LineEditDelegate *lEditeDelegate;
};

#endif // READINPUTWIN_H
