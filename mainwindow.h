#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adddevwin.h"
#include "removedevwin.h"
#include "databasethread.h"
#include "readwin.h"
#include "writewin.h"
#include "readcoilswin.h"
#include "readinputwin.h"
#include "writecoilwin.h"
#include "serportsettwin.h"
#include "propertyvaluedelegate.h"
#include "connectionthread.h"
#include "controlviewwin.h"
#include "breakerstablewin.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_actionREAD_triggered();

    void on_actionWRITE_triggered();

    void on_actionSerial_Port_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionREAD_COILS_triggered();

    void on_actionFORCE_SINGLE_COIL_triggered();

    void on_actionREAD_INPUT_triggered();

    void on_actionRemove_triggered();

    void on_actionControl_triggered();

    void on_actionEnum_Table_triggered();

    void on_actionBreakers_Table_triggered();

public slots:
    void readTableView_clicked(QString i);
    void writeTableView_clicked(QString i);

private:
    Ui::MainWindow *ui;
    DataBaseThread *dbThread;
    ConnectionThread *serThread;
    QSqlTableModel *devTable;
    QSqlTableModel *readRegTable;
    QSqlTableModel *writeRegTable;
    void updateDevTable(int first);
    void updateReadRegTable(int first);
    void updateWriteRegTable(int first);
    NotEditableDelegate *noEditRTableDelegate;
    PushButtonDelegate *btnRTableDelegate;
    NotEditableDelegate *noEditWTableDelegate;
    PushButtonDelegate *btnWTableDelegate;
    PropertyValueDelegate *valDelegate;
    QString PrjName;
    QString exePath = QDir::currentPath();

};
#endif // MAINWINDOW_H
