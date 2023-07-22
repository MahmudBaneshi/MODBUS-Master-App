#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbThread = DataBaseThread::getInstance(this);
    dbThread->databaseCommand = 1;
    dbThread->run();
    dbThread->wait();
    updateDevTable(1);
    updateReadRegTable(1);
    updateWriteRegTable(1);
    serThread = ConnectionThread::getInstance(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAdd_triggered()
{
    AddDevWin* devW = new AddDevWin(this);
    devW->exec();
    int re = devW->res;
    delete devW;
    updateDevTable(0);
    if(re == 2){
        updateReadRegTable(0);
        updateWriteRegTable(0);
    }
}

void MainWindow::updateDevTable(int first)
{
    if(sqlDb.open()){
        if(first){
            devTable = new QSqlTableModel(this, sqlDb);
            devTable->setTable("DEV");
            devTable->select();
            devTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView_2->setModel(devTable);
        }
        else {
            devTable->clear();
            devTable->setTable("DEV");
            devTable->select();
            ui->tableView_2->setModel(devTable);
        }
    }
}

void MainWindow::updateReadRegTable(int first)
{
    if(sqlDb.open()){
        if(first){
            readRegTable = new QSqlTableModel(this, sqlDb);
            noEditRTableDelegate = new NotEditableDelegate(this);
            btnRTableDelegate = new PushButtonDelegate(this);
            connect(btnRTableDelegate, SIGNAL(clickSignal(QString)), this, SLOT(readTableView_clicked(QString)));
            readRegTable->setTable("READ_DEV");
            readRegTable->select();
            readRegTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->setModel(readRegTable);
            ui->tableView->hideColumn(0);
            ui->tableView->hideColumn(3);
            ui->tableView->hideColumn(4);
            ui->tableView->hideColumn(5);
            ui->tableView->setItemDelegateForColumn(1, noEditRTableDelegate);
            ui->tableView->setItemDelegateForColumn(2, noEditRTableDelegate);
            ui->tableView->setItemDelegateForColumn(6, noEditRTableDelegate);
            ui->tableView->setItemDelegateForColumn(7, noEditRTableDelegate);
            ui->tableView->setItemDelegateForColumn(8, btnRTableDelegate);
        }
        else {
            readRegTable->clear();
            readRegTable->setTable("READ_DEV");
            readRegTable->select();
            ui->tableView->setModel(readRegTable);
            ui->tableView->hideColumn(0);
            ui->tableView->hideColumn(3);
            ui->tableView->hideColumn(4);
            ui->tableView->hideColumn(5);
        }
    }
}

void MainWindow::updateWriteRegTable(int first)
{
    if(sqlDb.open()){
        if(first){
            writeRegTable = new QSqlTableModel(this, sqlDb);
            noEditWTableDelegate = new NotEditableDelegate(this);
            btnWTableDelegate = new PushButtonDelegate(this);
            valDelegate = new PropertyValueDelegate(this);
            connect(btnWTableDelegate, SIGNAL(clickSignal(QString)), this, SLOT(writeTableView_clicked(QString)));
            writeRegTable->setTable("WRITE_DEV");
            writeRegTable->select();
            writeRegTable->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView_3->setModel(writeRegTable);
            ui->tableView_3->hideColumn(0);
            ui->tableView_3->hideColumn(3);
            ui->tableView_3->hideColumn(4);
            ui->tableView_3->hideColumn(5);
            ui->tableView_3->setItemDelegateForColumn(1, noEditWTableDelegate);
            ui->tableView_3->setItemDelegateForColumn(2, noEditWTableDelegate);

            ui->tableView_3->setItemDelegateForColumn(6, valDelegate);
            ui->tableView_3->setItemDelegateForColumn(7, noEditWTableDelegate);
            ui->tableView_3->setItemDelegateForColumn(8, btnWTableDelegate);
        }
        else {
            writeRegTable->clear();
            writeRegTable->setTable("WRITE_DEV");
            writeRegTable->select();
            ui->tableView_3->setModel(writeRegTable);
            ui->tableView_3->hideColumn(0);
            ui->tableView_3->hideColumn(3);
            ui->tableView_3->hideColumn(4);
            ui->tableView_3->hideColumn(5);
        }
    }
}

void MainWindow::on_actionREAD_triggered()
{
    ReadWin *rW = new ReadWin(this);
    rW->deleteLater();
    rW->exec();
    delete rW;
    updateReadRegTable(0);
}

void MainWindow::on_actionWRITE_triggered()
{
    WriteWin* wW = new WriteWin(this);
    wW->exec();
    delete wW;
    updateWriteRegTable(0);
}

void MainWindow::on_actionSerial_Port_triggered()
{
    SerPortSettWin* serSW = new SerPortSettWin(this);
    serSW->exec();
    delete serSW;
}
/*  next btn in p1  */
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/*  prv. btn in p1  */
void MainWindow::on_pushButton_2_clicked()
{

}
/*  next btn in p2  */
void MainWindow::on_pushButton_3_clicked()
{

}
/*  prv. btn in p2  */
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
/*  for when GET button clicked in read table view  */
void MainWindow::readTableView_clicked(QString i)
{
    if(COMPortName.isEmpty() || COMPortParity.isEmpty() || COMPortBaud.isEmpty()){
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setStyleSheet("background-color: rgb(53, 53, 53); color: rgb(255, 255, 255);");
        msg.setText("Select serial port From communication tab first!");
        msg.setWindowTitle("Warning");
        msg.exec();
        return;
    }
    #ifdef DEBUG_APP
    qDebug()<< "READ : " << i;
    #endif
    QStringList tmpId = i.split(',');
    dbThread->idToWrite.clear();
    dbThread->devAddrToWrite.clear();
    dbThread->addrToWrite.clear();
    dbThread->idToWrite = QString::number(tmpId.at(0).toInt() + 1);
    dbThread->databaseCommand = 9;
    dbThread->run();
    dbThread->wait();
    /**/
    serThread->devAddressToWrite = (uint8_t)dbThread->devAddrToWrite.toUInt();
    serThread->addressToWrite = (uint16_t)dbThread->addrToWrite.toUInt();
    serThread->numOfPoints = 1;
    serThread->idToWriteSer.clear();
    serThread->idToWriteSer = QString::number(tmpId.at(0).toInt() + 1);
    serThread->serialCommand = 1;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    serThread->run();
    serThread->wait();
    QApplication::restoreOverrideCursor();
    if(serThread->commandResult == COMMAND_NOT_SUCCESSFUL){
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setStyleSheet("background-color: rgb(53, 53, 53); color: rgb(255, 255, 255);");
        msg.setText("Couldn't read the property!");
        msg.setWindowTitle("Warning");
        msg.exec();
        return;
    }
    updateReadRegTable(0);
}
/*  for when SEND button clicked in write table view  */
void MainWindow::writeTableView_clicked(QString i)
{
    if(COMPortName.isEmpty() || COMPortParity.isEmpty() || COMPortBaud.isEmpty()){
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setStyleSheet("background-color: rgb(53, 53, 53); color: rgb(255, 255, 255);");
        msg.setText("Select serial port From communication tab first!");
        msg.setWindowTitle("Warning");
        msg.exec();
        return;
    }
    #ifdef DEBUG_APP
    qDebug()<< "WRITE : " << i;
    #endif
    QStringList tmpId = i.split(',');
    dbThread->idToWrite.clear();
    dbThread->devAddrToWrite.clear();
    dbThread->addrToWrite.clear();
    dbThread->dataToWrite.clear();
    dbThread->idToWrite = QString::number(tmpId.at(0).toInt() + 1);
    dbThread->databaseCommand = 8;
    dbThread->run();
    dbThread->wait();
    /**/
    serThread->devAddressToWrite = (uint8_t)dbThread->devAddrToWrite.toUInt();
    serThread->addressToWrite = (uint16_t)dbThread->addrToWrite.toUInt();
    serThread->dataToWrite = (uint16_t)dbThread->dataToWrite.toUInt();
    serThread->serialCommand = 2;
    QApplication::setOverrideCursor(Qt::WaitCursor);

    serThread->run();
    serThread->wait();
    QApplication::restoreOverrideCursor();
    if(serThread->commandResult == COMMAND_NOT_SUCCESSFUL){
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setStyleSheet("background-color: rgb(53, 53, 53); color: rgb(255, 255, 255);");
        msg.setText("Couldn't write the property!");
        msg.setWindowTitle("Warning");
        msg.exec();
        return;
    }
    updateWriteRegTable(0);
}
/**/
void MainWindow::on_actionOpen_triggered()
{
    QString fileO = QFileDialog::getOpenFileName(this,
                                                            tr("Open file"), "", tr("MDB (*.MDB *.mdb)"));
    if(fileO.size()){
        if (QFile::exists(exePath + "/MODBUS")){
            QFile::remove(exePath + "/MODBUS");
        }
        bool status = QFile::copy(fileO, exePath + "/MODBUS");
        if(status){
            updateWriteRegTable(0);
            updateDevTable(0);
            updateReadRegTable(0);
        }
        else{
            QMessageBox errMsgBox;
            errMsgBox.setText("file did'nt open try open the program with run as administrator option!");
            errMsgBox.exec();
        }
    }
}
/**/
void MainWindow::on_actionNew_triggered()
{
    dbThread->databaseCommand = 1;
    dbThread->run();
    dbThread->wait();
    updateDevTable(0);
    updateReadRegTable(0);
    updateWriteRegTable(0);
}
/**/
void MainWindow::on_actionSave_triggered()
{
    if(PrjName.isEmpty()){
        QString fileS = QFileDialog::getSaveFileName(this,
                                                            tr("Save file"), "", tr("MDB (*.MDB *.mdb)"));
        if(fileS.size()){
            if(!(fileS.contains(".mdb") || fileS.contains(".MDB"))){
                fileS += ".MDB";
            }
            PrjName = fileS;
            if (QFile::exists(PrjName)){
                QFile::remove(PrjName);
            }
            QFile::copy(exePath + "/MODBUS", PrjName);
        }
    }
    else {
        if (QFile::exists(PrjName)){
            QFile::remove(PrjName);
        }
        QFile::copy(exePath + "/MODBUS", PrjName);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileS = QFileDialog::getSaveFileName(this,
                                                      tr("Save file"), "", tr("MDB (*.MDB *.mdb)"));
    if(fileS.size()){
        if(!(fileS.contains(".mdb") || fileS.contains(".MDB"))){
            fileS += ".MDB";
        }
        PrjName.clear();
        PrjName = fileS;
        if (QFile::exists(PrjName)){
            QFile::remove(PrjName);
        }
        QFile::copy(exePath + "/MODBUS", PrjName);
    }
}
/*  Read Coil Win  */
void MainWindow::on_actionREAD_COILS_triggered()
{
    ReadCoilsWin* rCW = new ReadCoilsWin(this);
    rCW->exec();
    delete rCW;
}
/*  Write Coil Win  */
void MainWindow::on_actionFORCE_SINGLE_COIL_triggered()
{
    WriteCoilWin* wCW = new WriteCoilWin(this);
    wCW->exec();
    delete wCW;
}
/*  Read Input Win  */
void MainWindow::on_actionREAD_INPUT_triggered()
{
    ReadInputWin* rIW = new ReadInputWin(this);
    rIW->exec();
    delete rIW;
}

void MainWindow::on_actionRemove_triggered()
{
    RemoveDevWin* devRW = new RemoveDevWin(this);
    devRW->exec();
    delete devRW;
    updateDevTable(0);
}
/*  Control Win  */
void MainWindow::on_actionControl_triggered()
{
    ControlViewWin* cW = new ControlViewWin(this);
    cW->exec();
    delete cW;
}
/*  Enums Win  */
void MainWindow::on_actionEnum_Table_triggered()
{

}
/*  breakers Win  */
void MainWindow::on_actionBreakers_Table_triggered()
{
    BreakersTableWin* bW = new BreakersTableWin(this);
    bW->exec();
    delete bW;
}
