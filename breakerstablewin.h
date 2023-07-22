#ifndef BREAKERSTABLEWIN_H
#define BREAKERSTABLEWIN_H

#include <QDialog>
#include "databasethread.h"
#include "noteditabledelegate.h"
#include "comboboxdelegate.h"
#include "lineeditdelegate.h"


namespace Ui {
class BreakersTableWin;
}

class BreakersTableWin : public QDialog
{
    Q_OBJECT

public:
    explicit BreakersTableWin(QWidget *parent = nullptr);
    ~BreakersTableWin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BreakersTableWin *ui;
    DataBaseThread *dbThread;
    void updateModel(int first);
    QSqlTableModel *brTable;
    ComboBoxDelegate *inputsDelegate;
    ComboBoxDelegate *coilsDelegate;
    NotEditableDelegate *noEditDelegate;
    LineEditDelegate *lEditeDelegate;
};

#endif // BREAKERSTABLEWIN_H
