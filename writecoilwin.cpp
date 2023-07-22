#include "writecoilwin.h"
#include "ui_writecoilwin.h"

WriteCoilWin::WriteCoilWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteCoilWin)
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

WriteCoilWin::~WriteCoilWin()
{
    delete ui;
    delete writeCoilsTable;
    delete noEditDelegate;
    delete spinDelegate;
}

void WriteCoilWin::updateModel(int first)
{
    if(sqlDb.open()){
        if(first){
            writeCoilsTable = new QSqlTableModel(this, sqlDb);
            writeCoilsTable->setTable("FORCE_COIL");
            writeCoilsTable->select();
            writeCoilsTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->setModel(writeCoilsTable);
            noEditDelegate = new NotEditableDelegate(this);
            spinDelegate = new SpinBoxDelegate(this);
            lEditeDelegate = new LineEditDelegate(this);
            spinDelegate->Max_R = 65535;
            spinDelegate->Min_R = 0;
            ui->tableView->setItemDelegateForColumn(0, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(1, noEditDelegate);
            ui->tableView->setItemDelegateForColumn(2, lEditeDelegate);
            ui->tableView->setItemDelegateForColumn(3, spinDelegate);

            ui->tableView->hideColumn(4);
            ui->tableView->hideColumn(5);
            ui->tableView->hideColumn(6);
        }
        else {
            writeCoilsTable->clear();
            writeCoilsTable->setTable("FORCE_COIL");
            writeCoilsTable->select();
            ui->tableView->setModel(writeCoilsTable);
            if(ui->comboBox->currentText() != "NONE"){
                writeCoilsTable->setFilter("[DEV Address] = " + ui->comboBox->currentText());
            }
            ui->tableView->hideColumn(4);
            ui->tableView->hideColumn(5);
            ui->tableView->hideColumn(6);
        }
    }
}

void WriteCoilWin::on_comboBox_activated(const QString &)
{
    updateModel(0);
}
/*  remove  */
void WriteCoilWin::on_pushButton_2_clicked()
{

}
/*  add  */
void WriteCoilWin::on_pushButton_clicked()
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
        dbThread->databaseCommand = 11;
        dbThread->devA = ui->comboBox->currentText();
        dbThread->run();
        dbThread->wait();
        updateModel(0);
    }
}
