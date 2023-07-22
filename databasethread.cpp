#include "databasethread.h"

QSqlDatabase sqlDb;


DataBaseThread::DataBaseThread(QObject *parent) : QThread(parent)
{
    path += "/MODBUS";
    if(sqlDb.isOpen()){
        sqlDb.close();
    }
    QSqlDatabase::removeDatabase(path);
    sqlDb = QSqlDatabase::addDatabase("QSQLITE", "MAIN_CONNECTION");
    sqlDb.setDatabaseName(path);
}

DataBaseThread::~DataBaseThread()
{
    if(sqlDb.isOpen()){
        sqlDb.close();
    }
    QSqlDatabase::removeDatabase(path);
}

void DataBaseThread::run()
{
    /*  create tables at startup of the app   */
    if(databaseCommand == 1){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            /**/
            query.prepare("DROP TABLE [DEV];");
            query.exec();
            query.exec("CREATE TABLE [DEV] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[Name] TEXT NOT NULL, "
                           "[addr] TEXT NOT NULL);");
            /**/
            query.prepare("DROP TABLE [READ_DEV];");
            query.exec();
            query.exec("CREATE TABLE [READ_DEV] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[DEV Address] TEXT NOT NULL, "
                           "[Property Name] TEXT NOT NULL, "
                           "[Property Address] TEXT NOT NULL, "
                           "[Property Type] TEXT NOT NULL, "
                           "[Property Range] TEXT NOT NULL, "
                           "[Property Value] TEXT NOT NULL, "
                           "[UNIT] TEXT NOT NULL, "
                           "[Get from Device] TEXT NOT NULL);");
            /**/
            query.prepare("DROP TABLE [WRITE_DEV];");
            query.exec();
            query.exec("CREATE TABLE [WRITE_DEV] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[DEV Address] TEXT NOT NULL, "
                           "[Property Name] TEXT NOT NULL, "
                           "[Property Address] TEXT NOT NULL, "
                           "[Property Type] TEXT NOT NULL, "
                           "[Property Range] TEXT NOT NULL, "
                           "[Property Value] TEXT NOT NULL, "
                           "[UNIT] TEXT NOT NULL, "
                           "[Send to Device] TEXT NOT NULL);");
            /**/
            query.prepare("DROP TABLE [ENUM_TABLE];");
            query.exec();
            query.exec("CREATE TABLE [ENUM_TABLE] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[DEV Address] TEXT NOT NULL, "
                           "[Property Address] TEXT NOT NULL, "
                           "[Property Value] TEXT NOT NULL, "
                           "[Property Txt] TEXT NOT NULL);");
            /**/
            query.prepare("DROP TABLE [READ_COILS];");
            query.exec();
            query.exec("CREATE TABLE [READ_COILS] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[DEV Address] TEXT NOT NULL, "
                           "[Name] TEXT NOT NULL, "
                           "[Property Address] TEXT NOT NULL, "
                           "[Property Value] TEXT NOT NULL, "
                           "[Read] TEXT NOT NULL);");
            /**/
            query.prepare("DROP TABLE [READ_INPUT];");
            query.exec();
            query.exec("CREATE TABLE [READ_INPUT] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[DEV Address] TEXT NOT NULL, "
                           "[Name] TEXT NOT NULL, "
                           "[Property Address] TEXT NOT NULL, "
                           "[Property Value] TEXT NOT NULL, "
                           "[Read] TEXT NOT NULL);");
            /**/
            query.prepare("DROP TABLE [FORCE_COIL];");
            query.exec();
            query.exec("CREATE TABLE [FORCE_COIL] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[DEV Address] TEXT NOT NULL, "
                           "[Name] TEXT NOT NULL, "
                           "[Property Address] TEXT NOT NULL, "
                           "[Property Value] TEXT NOT NULL, "
                           "[Description] TEXT NOT NULL, "
                           "[Send to Device] TEXT NOT NULL);");

            /**/
            query.prepare("DROP TABLE [BREAKER];");
            query.exec();
            query.exec("CREATE TABLE [BREAKER] ( "
                           "id INTEGER PRIMARY KEY, "
                           "[NAME] TEXT NOT NULL, "
                           "[INPUT52_A] TEXT NOT NULL, "
                           "[INPUT52_B] TEXT NOT NULL, "
                           "[TRIP] TEXT NOT NULL, "
                           "[CLOSE] TEXT NOT NULL, "
                           "[DESCRIPTION] TEXT NOT NULL);");
        }
    }
    /*  insert into device table  */
    if(databaseCommand == 2){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [DEV]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }
            query.prepare("INSERT INTO [DEV] (id, [Name], [Addr]) "
                          "VALUES (:id, :name, :ser)");
            query.bindValue(":id", cnt);
            query.bindValue(":name", devN);
            query.bindValue(":ser", devA);
            query.exec();

        }
    }
    /*  get devices addresses  */
    if(databaseCommand == 3){
        if(sqlDb.open()){
            devAdds.clear();
            QSqlQuery query(sqlDb);
            query.exec("SELECT addr FROM [DEV]");
            while (query.next()) {
                devAdds.append(query.value(0).toString());
            }
        }
    }
    /*  insert into read table  */
    if(databaseCommand == 4){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [READ_DEV]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }

            query.prepare("INSERT INTO [READ_DEV] (id, [DEV Address], [Property Name], [Property Address], "
                          "[Property Type], [Property Range], [Property Value], [UNIT], [Get from Device]) "
                          "VALUES (:id, :name, :ser, :ser1, :ser2, :ser3, :ser4, :ser5, :ser6)");
            query.bindValue(":id", cnt);
            query.bindValue(":name", devA);
            query.bindValue(":ser", "-");
            query.bindValue(":ser1", "0");
            query.bindValue(":ser2", "Bool");
            query.bindValue(":ser3", "0-1");
            query.bindValue(":ser4", "0");
            query.bindValue(":ser5", "0");
            query.bindValue(":ser6", "GET");
            query.exec();
        }
    }
    /*  insert into write table  */
    if(databaseCommand == 5){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [WRITE_DEV]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }

            query.prepare("INSERT INTO [WRITE_DEV] (id, [DEV Address], [Property Name], [Property Address], "
                          "[Property Type], [Property Range], [Property Value], [UNIT], [Send to Device]) "
                          "VALUES (:id, :name, :ser, :ser1, :ser2, :ser3, :ser4, :ser5, :ser6)");
            query.bindValue(":id", cnt);
            query.bindValue(":name", devA);
            query.bindValue(":ser", "-");
            query.bindValue(":ser1", "0");
            query.bindValue(":ser2", "Bool");
            query.bindValue(":ser3", "0-1");
            query.bindValue(":ser4", "0");
            query.bindValue(":ser5", "0");
            query.bindValue(":ser6", "SEND");
            query.exec();
        }
    }
    /*  insert into read coil table  */
    if(databaseCommand == 6){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [READ_COILS]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }
            query.prepare("INSERT INTO [READ_COILS] (id, [DEV Address], [Name], [Property Address], [Property Value], [Read]) "
                          "VALUES (:id, :dev, :ssss, :name, :ser, :reed)");
            query.bindValue(":id", cnt);
            query.bindValue(":dev", devA);
            query.bindValue(":ssss", "-");
            query.bindValue(":name", "0");
            query.bindValue(":ser", "0");
            query.bindValue(":reed", "READ");
            query.exec();

        }
    }
    /*  insert into read input table  */
    if(databaseCommand == 7){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [READ_INPUT]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }
            query.prepare("INSERT INTO [READ_INPUT] (id, [DEV Address], [Name], [Property Address], [Property Value], [Read]) "
                          "VALUES (:id, :dev, :ssss, :name, :ser, :reed)");
            query.bindValue(":id", cnt);
            query.bindValue(":dev", devA);
            query.bindValue(":ssss", "-");
            query.bindValue(":name", "0");
            query.bindValue(":ser", "0");
            query.bindValue(":reed", "READ");
            query.exec();

        }
    }
    /*  insert into force coil table  */
    if(databaseCommand == 11){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [FORCE_COIL]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }
            query.prepare("INSERT INTO [FORCE_COIL] (id, [DEV Address], [Name], [Property Address], [Property Value], [Description], [Send to Device]) "
                          "VALUES (:id, :dev, :ssss, :name, :ser, :ser1, :ser2)");
            query.bindValue(":id", cnt);
            query.bindValue(":dev", devA);
            query.bindValue(":ssss", "-");
            query.bindValue(":name", "0");
            query.bindValue(":ser", "0");
            query.bindValue(":ser1", "-");
            query.bindValue(":ser2", "SEND");
            query.exec();

        }
    }
    /*  Get data to write  */
    if(databaseCommand == 8){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT [DEV Address], [Property Address], [Property Value] FROM [WRITE_DEV] WHERE id = " + idToWrite);
            while (query.next()) {
                #ifdef DEBUG_APP
                qDebug()<< idToWrite << " : " << query.value(0) << query.value(1) << query.value(2);
                #endif
                devAddrToWrite = query.value(0).toString();
                addrToWrite = query.value(1).toString();
                dataToWrite = query.value(2).toString();

            }

        }
    }
    /*  Get data to read  */
    if(databaseCommand == 9){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT [DEV Address], [Property Address] FROM [READ_DEV] WHERE id = " + idToWrite);
            while (query.next()) {
                #ifdef DEBUG_APP
                qDebug()<< idToWrite << " : " << query.value(0) << query.value(1);
                #endif
                devAddrToWrite = query.value(0).toString();
                addrToWrite = query.value(1).toString();

            }

        }
    }
    /*  Update Read Data  */
    if(databaseCommand == 10){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            #ifdef DEBUG_APP
            qDebug()<< "DB : " << idToWrite << " : " << dataFromReadDb;
            #endif
            query.exec("UPDATE [READ_DEV] SET [Property Value]=" + dataFromReadDb + " WHERE id = " + idToWrite);

        }
    }
    /*  insert to read table when adding a device  */
    if(databaseCommand == 11){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [READ_DEV]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }

            query.prepare("INSERT INTO [READ_DEV] (id, [DEV Address], [Property Name], [Property Address], "
                          "[Property Type], [Property Range], [Property Value], [UNIT], [Get from Device]) "
                          "VALUES (:id, :name, :ser, :ser1, :ser2, :ser3, :ser4, :ser5, :ser6)");
            query.bindValue(":id", cnt);
            query.bindValue(":name", devA);
            query.bindValue(":ser", propertyN);
            query.bindValue(":ser1", propertyA);
            query.bindValue(":ser2", propertyT);
            query.bindValue(":ser3", propertyR);
            query.bindValue(":ser4", "0");
            query.bindValue(":ser5", propertyU);
            query.bindValue(":ser6", "GET");
            query.exec();
        }
    }
    /*  insert to write table when adding a device  */
    if(databaseCommand == 12){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [WRITE_DEV]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }

            query.prepare("INSERT INTO [WRITE_DEV] (id, [DEV Address], [Property Name], [Property Address], "
                          "[Property Type], [Property Range], [Property Value], [UNIT], [Send to Device]) "
                          "VALUES (:id, :name, :ser, :ser1, :ser2, :ser3, :ser4, :ser5, :ser6)");
            query.bindValue(":id", cnt);
            query.bindValue(":name", devA);
            query.bindValue(":ser", propertyN);
            query.bindValue(":ser1", propertyA);
            query.bindValue(":ser2", propertyT);
            query.bindValue(":ser3", propertyR);
            query.bindValue(":ser4", "0");
            query.bindValue(":ser5", propertyU);
            query.bindValue(":ser6", "SEND");
            query.exec();
        }
    }
    /*  insert into breaker table  */
    if(databaseCommand == 13){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            query.exec("SELECT id FROM [BREAKER]");
            int cnt = 1;
            while (query.next()) {
                cnt++;
            }
            query.prepare("INSERT INTO [BREAKER] (id, [NAME], [INPUT52_A], [INPUT52_B], [TRIP], [CLOSE], [DESCRIPTION]) "
                          "VALUES (:id, :name, :ser, :ser1, :ser2, :ser3, :ser4)");
            query.bindValue(":id", cnt);
            query.bindValue(":name", "BREAKER-" + QString::number(cnt));
            query.bindValue(":ser", "-");
            query.bindValue(":ser1", "-");
            query.bindValue(":ser2", "-");
            query.bindValue(":ser3", "-");
            query.bindValue(":ser4", "-");
            query.exec();

        }
    }
    /*  get coils name and inputs name  */
    if(databaseCommand == 14){
        if(sqlDb.open()){
            QSqlQuery query(sqlDb);
            coilsName.clear();
            inputsName.clear();
            query.exec("SELECT [Name] FROM [FORCE_COIL]");
            while (query.next()) {
                coilsName.append(query.value(0).toString());
            }
            query.exec("SELECT [Name] FROM [READ_INPUT]");
            while (query.next()) {
                inputsName.append(query.value(0).toString());
            }


        }
    }
    /*  get breakers  */
    if(databaseCommand == 15){
        if(sqlDb.open()){
            brNames.clear();
            brInputANames.clear();
            brInputBNames.clear();
            brTripBNames.clear();
            brCloseBNames.clear();
            QSqlQuery query(sqlDb);
            query.exec("SELECT [NAME], [INPUT52_A], [INPUT52_B], [TRIP], [CLOSE] FROM [BREAKER]");
            while (query.next()) {
                brNames.append(query.value(0).toString());
                brInputANames.append(query.value(1).toString());
                brInputBNames.append(query.value(2).toString());
                brTripBNames.append(query.value(3).toString());
                brCloseBNames.append(query.value(4).toString());
            }

        }
    }
}

DataBaseThread *DataBaseThread::getInstance(QObject *parent)
{
    static DataBaseThread *instance = nullptr;
    if(instance == nullptr){
        instance = new DataBaseThread(parent);
    }
    return instance;
}
