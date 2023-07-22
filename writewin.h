#ifndef WRITEWIN_H
#define WRITEWIN_H

#include <QDialog>
#include "databasethread.h"
#include "comboboxdelegate.h"
#include "noteditabledelegate.h"
#include "spinboxdelegate.h"
#include "lineeditdelegate.h"

namespace Ui {
class WriteWin;
}

class WriteWin : public QDialog
{
    Q_OBJECT

public:
    explicit WriteWin(QWidget *parent = nullptr);
    ~WriteWin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::WriteWin *ui;
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

#endif // WRITEWIN_H
