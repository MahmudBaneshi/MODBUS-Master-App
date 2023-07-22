#ifndef READCOILSWIN_H
#define READCOILSWIN_H

#include <QDialog>
#include "databasethread.h"
#include "noteditabledelegate.h"
#include "spinboxdelegate.h"
#include "lineeditdelegate.h"

namespace Ui {
class ReadCoilsWin;
}

class ReadCoilsWin : public QDialog
{
    Q_OBJECT

public:
    explicit ReadCoilsWin(QWidget *parent = nullptr);
    ~ReadCoilsWin();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ReadCoilsWin *ui;
    void updateModel(int first);
    DataBaseThread *dbThread;
    QSqlTableModel *readCoilsTable;
    NotEditableDelegate *noEditDelegate;
    SpinBoxDelegate *spinDelegate;
    LineEditDelegate *lEditeDelegate;
};

#endif // READCOILSWIN_H
