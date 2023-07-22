#include "adddevwin.h"
#include "ui_adddevwin.h"

AddDevWin::AddDevWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDevWin)
{
    ui->setupUi(this);
    dbThread = DataBaseThread::getInstance(this);
    res = 0;
    ui->lineEdit->setText(devName);
    ui->spinBox->setValue(devAdd);
}

AddDevWin::~AddDevWin()
{
    delete ui;
}

void AddDevWin::on_buttonBox_accepted()
{
    if(ui->checkBox->isChecked()){
        res = 2;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QSqlDatabase sqlDevDb;
        QSqlDatabase::removeDatabase(fileO);
        sqlDevDb = QSqlDatabase::addDatabase("QSQLITE", "FIRST_CONNECTION");
        sqlDevDb.setDatabaseName(fileO);
        if(sqlDevDb.open()){
            QSqlQuery query(sqlDevDb);
            query.exec("SELECT [Name], [addr] FROM [DEV]");
            while (query.next()) {
                devAdd = query.value(1).toInt();
                devName = query.value(0).toString();
                dbThread->devN = devName;
                dbThread->devA = QString::number(devAdd);
                dbThread->databaseCommand = 2;
                dbThread->run();
                dbThread->wait();
            }
            query.exec("SELECT [DEV Address], [Property Name], [Property Address], "
                       "[Property Type], [Property Range], [Property Value], [UNIT], [Get from Device] FROM [READ_DEV]");
            while (query.next()) {
                devAdd = query.value(0).toInt();
                dbThread->devA = QString::number(devAdd);
                dbThread->propertyN = query.value(1).toString();
                dbThread->propertyA = query.value(2).toString();
                dbThread->propertyT = query.value(3).toString();
                dbThread->propertyR = query.value(4).toString();
                dbThread->propertyU = query.value(6).toString();

                dbThread->databaseCommand = 11;
                dbThread->run();
                dbThread->wait();
            }

            query.exec("SELECT [DEV Address], [Property Name], [Property Address], "
                       "[Property Type], [Property Range], [Property Value], [UNIT], [Send to Device] FROM [WRITE_DEV]");
            while (query.next()) {
                devAdd = query.value(0).toInt();
                dbThread->devA = QString::number(devAdd);
                dbThread->propertyN = query.value(1).toString();
                dbThread->propertyA = query.value(2).toString();
                dbThread->propertyT = query.value(3).toString();
                dbThread->propertyR = query.value(4).toString();
                dbThread->propertyU = query.value(6).toString();

                dbThread->databaseCommand = 12;
                dbThread->run();
                dbThread->wait();
            }

        }

        QApplication::restoreOverrideCursor();
        this->close();
        return;
    }
    res = 1;
    devAdd = ui->spinBox->value();
    devName = ui->lineEdit->text();
    dbThread->devN = devName;
    dbThread->devA = QString::number(devAdd);
    dbThread->databaseCommand = 2;
    dbThread->run();
    dbThread->wait();
    this->close();
}

void AddDevWin::on_buttonBox_rejected()
{
    res = 0;
    this->close();
}
/*  import  */
void AddDevWin::on_pushButton_clicked()
{
    fileO.clear();
    fileO = QFileDialog::getOpenFileName(this,
                                                            tr("Open file"), "", tr("MDB (*.MDB *.mdb)"));
    if(fileO.size()){
        ui->lineEdit_2->setText(fileO);
        QSqlDatabase sqlDevDb;
        QSqlDatabase::removeDatabase(fileO);
        sqlDevDb = QSqlDatabase::addDatabase("QSQLITE", "FIRST_CONNECTION");
        sqlDevDb.setDatabaseName(fileO);
        if(sqlDevDb.open()){
            QSqlQuery query(sqlDevDb);
            query.exec("SELECT id FROM [DEV]");
            int cnt = 0;
            while (query.next()) {
                cnt++;
            }
            if(cnt == 0){
                ui->label_3->setText("No device is in this database!");
            }
            else if(cnt == 1){
                ui->label_3->setText("1 device is in this database! All devices will be addedd to project");
            }
            else {
                ui->label_3->setText(QString::number(cnt) + " devices is in this database! All devices will be addedd to project");
            }
        }
        else{
            QMessageBox errMsgBox;
            errMsgBox.setText("file did'nt open try open the program with run as administrator option!");
            errMsgBox.exec();
        }

    }
}
