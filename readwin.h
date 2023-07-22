#ifndef READWIN_H
#define READWIN_H

#include <QDialog>
#include "databasethread.h"
#include "comboboxdelegate.h"
#include "noteditabledelegate.h"
#include "spinboxdelegate.h"
#include "lineeditdelegate.h"
#include "pushbuttondelegate.h"

namespace Ui {
class ReadWin;
}

class ReadWin : public QDialog
{
    Q_OBJECT

public:
    explicit ReadWin(QWidget *parent = nullptr);
    ~ReadWin();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ReadWin *ui;
    DataBaseThread *dbThread;
    void updateModel(int first);
    QSqlTableModel *readDevTable;
    ComboBoxDelegate *dataTypeDelegate;
    NotEditableDelegate *noEditDelegate;
    SpinBoxDelegate *spinDelegate;
    LineEditDelegate *lEditeDelegate;
    LineEditDelegate *lEditeDelegate_2;
    LineEditDelegate *lEditeDelegate_3;
};

#endif // READWIN_H
