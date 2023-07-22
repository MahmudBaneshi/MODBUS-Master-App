#include "readinputwin.h"
#include "ui_readinputwin.h"

ReadInputWin::ReadInputWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadInputWin)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Window | Qt::WindowSystemMenuHint
                                | Qt::WindowMinimizeButtonHint
                                | Qt::WindowMaximizeButtonHint
                                | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    dbThread = DataBaseThread::getInstance(this);
    updateModel(1);
    dbThread->databaseCommand = 3;
    dbThread->run();
    dbThread->wait();
    ui->comboBox->addItem("NONE");
    ui->comboBox->addItems(dbThread->devAdds);
}

ReadInputWin::~ReadInputWin()
{
    delete ui;
    delete readInTable;
    delete noEditDelegate;
    delete spinDelegate;
}

void ReadInputWin::updateModel(int first)
{
    if(sqlDb.open()){
        if(first){
            readInTable = new QSqlTableModel(this, sqlDb);
            readInTable->setTable("READ_INPUT");
            readInTable->select();
            readInTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->setModel(readInTable);
            noEditDelegate = new NotEditableDelegate(this);
            lEditeDelegate = new LineEditDelegate(this);
            spinDelegate = new SpinBoxDelegate(this);
            spinDelegate->Max_R = 65535;
            spinDelegate->Min_R = 0;
            ui->tableView->setItemDelegateForColumn(0, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(1, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(2, lEditeDelegate);
            ui->tableView->setItemDelegateForColumn(3, spinDelegate);

            ui->tableView->hideColumn(4);
            ui->tableView->hideColumn(5);
        }
        else {
            readInTable->clear();
            readInTable->setTable("READ_INPUT");
            readInTable->select();
            ui->tableView->setModel(readInTable);
            if(ui->comboBox->currentText() != "NONE"){
                readInTable->setFilter("[DEV Address] = " + ui->comboBox->currentText());
            }
            ui->tableView->hideColumn(4);
            ui->tableView->hideColumn(5);
        }
    }
}

void ReadInputWin::on_comboBox_activated(const QString &)
{
    updateModel(0);
}
/*  remove  */
void ReadInputWin::on_pushButton_2_clicked()
{

}
/*  add  */
void ReadInputWin::on_pushButton_clicked()
{
    if(ui->comboBox->currentText() == "NONE"){
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setStyleSheet("background-color: rgb(53, 53, 53); color: rgb(255, 255, 255);");
        msg.setText("Choose Device Addr. first!");
        msg.setWindowTitle("Warning");
        msg.exec();
        return;
    }
    else{
        dbThread->databaseCommand = 7;
        dbThread->devA = ui->comboBox->currentText();
        dbThread->run();
        dbThread->wait();
        updateModel(0);
    }
}
