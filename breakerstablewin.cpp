#include "breakerstablewin.h"
#include "ui_breakerstablewin.h"

BreakersTableWin::BreakersTableWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BreakersTableWin)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Window | Qt::WindowSystemMenuHint
                                | Qt::WindowMinimizeButtonHint
                                | Qt::WindowMaximizeButtonHint
                                | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    dbThread = DataBaseThread::getInstance(this);
    updateModel(1);
}

BreakersTableWin::~BreakersTableWin()
{
    delete brTable;
    delete inputsDelegate;
    delete noEditDelegate;
    delete coilsDelegate;
    delete ui;
}
/*  add  */
void BreakersTableWin::on_pushButton_clicked()
{
    dbThread->databaseCommand = 13;
    dbThread->run();
    dbThread->wait();
    updateModel(0);
}
/*  remove  */
void BreakersTableWin::on_pushButton_2_clicked()
{

}

void BreakersTableWin::updateModel(int first)
{
    if(sqlDb.open()){
        if(first){
            brTable = new QSqlTableModel(this, sqlDb);
            brTable->setTable("BREAKER");
            brTable->select();
            brTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->setModel(brTable);
            inputsDelegate = new ComboBoxDelegate(this);
            inputsDelegate->whichItems = 15;
            coilsDelegate = new ComboBoxDelegate(this);
            coilsDelegate->whichItems = 15;
            dbThread->databaseCommand = 14;
            dbThread->run();
            dbThread->wait();
            inputsDelegate->costumItems = dbThread->inputsName;
            coilsDelegate->costumItems = dbThread->coilsName;
            #ifdef DEBUG_APP
            qDebug()<< inputsDelegate->costumItems  << coilsDelegate->costumItems;
            #endif
            noEditDelegate = new NotEditableDelegate(this);
            lEditeDelegate = new LineEditDelegate(this);
            ui->tableView->setItemDelegateForColumn(0, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(1, lEditeDelegate);
            ui->tableView->setItemDelegateForColumn(2, inputsDelegate);
            ui->tableView->setItemDelegateForColumn(3, inputsDelegate);
            ui->tableView->setItemDelegateForColumn(4, coilsDelegate);
            ui->tableView->setItemDelegateForColumn(5, coilsDelegate);


            ui->tableView->hideColumn(6);
        }
        else {
            brTable->clear();
            brTable->setTable("BREAKER");
            brTable->select();
            ui->tableView->setModel(brTable);
            ui->tableView->hideColumn(6);
        }
    }
}
