#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#define DEBUG_APP
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

extern QSqlDatabase sqlDb;
extern QString COMPortName;
extern QString COMPortParity;
extern QString COMPortBaud;


#endif // SHAREDDATA_H
