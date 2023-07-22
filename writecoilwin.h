#ifndef WRITECOILWIN_H
#define WRITECOILWIN_H

#include <QDialog>
#include "databasethread.h"
#include "noteditabledelegate.h"
#include "spinboxdelegate.h"
#include "lineeditdelegate.h"

namespace Ui {
class WriteCoilWin;
}

class WriteCoilWin : public QDialog
{
    Q_OBJECT

public:
    explicit WriteCoilWin(QWidget *parent = nullptr);
    ~WriteCoilWin();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::WriteCoilWin *ui;
    void updateModel(int first);
    DataBaseThread *dbThread;
    QSqlTableModel *writeCoilsTable;
    NotEditableDelegate *noEditDelegate;
    SpinBoxDelegate *spinDelegate;
    LineEditDelegate *lEditeDelegate;
};

#endif // WRITECOILWIN_H
