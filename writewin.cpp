#include "writewin.h"
#include "ui_writewin.h"

WriteWin::WriteWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteWin)
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

WriteWin::~WriteWin()
{
    delete ui;
}
/*  add  */
void WriteWin::on_pushButton_clicked()
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
        dbThread->databaseCommand = 5;
        dbThread->devA = ui->comboBox->currentText();
        dbThread->run();
        dbThread->wait();
        updateModel(0);
    }
}
/*  remove  */
void WriteWin::on_pushButton_2_clicked()
{

}

void WriteWin::on_comboBox_activated(const QString &)
{
    updateModel(0);
}

void WriteWin::updateModel(int first)
{
    if(sqlDb.open()){
        if(first){
            readDevTable = new QSqlTableModel(this, sqlDb);
            readDevTable->setTable("WRITE_DEV");
            readDevTable->select();
            readDevTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->setModel(readDevTable);
            dataTypeDelegate = new ComboBoxDelegate(this);
            dataTypeDelegate->whichItems = 14;
            noEditDelegate = new NotEditableDelegate(this);
            spinDelegate = new SpinBoxDelegate(this);
            spinDelegate->Max_R = 65535;
            spinDelegate->Min_R = 0;
            lEditeDelegate = new LineEditDelegate(this);
            lEditeDelegate_2 = new LineEditDelegate(this);
            lEditeDelegate_2->inMask = "00000-00000";
            lEditeDelegate_3 = new LineEditDelegate(this);
            lEditeDelegate_3->inMask = "00000.00000 A";
            ui->tableView->setItemDelegateForColumn(0, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(1, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(2, lEditeDelegate);
            ui->tableView->setItemDelegateForColumn(3, spinDelegate);
            ui->tableView->setItemDelegateForColumn(4, dataTypeDelegate);
            ui->tableView->setItemDelegateForColumn(5, lEditeDelegate_2);
            ui->tableView->setItemDelegateForColumn(7, lEditeDelegate_3);

            ui->tableView->hideColumn(6);
            ui->tableView->hideColumn(8);
        }
        else {
            readDevTable->clear();
            readDevTable->setTable("WRITE_DEV");
            readDevTable->select();
            ui->tableView->setModel(readDevTable);
            if(ui->comboBox->currentText() != "NONE"){
                readDevTable->setFilter("[DEV Address] = " + ui->comboBox->currentText());
            }
            ui->tableView->hideColumn(6);
            ui->tableView->hideColumn(8);
        }
    }
}
