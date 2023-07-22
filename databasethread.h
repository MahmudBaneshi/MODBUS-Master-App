#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QObject>
#include <QThread>
#include <QtCore/QDir>
#include "shareddata.h"

/*
 *   this is based on singelton design pattern
 *   it can be used in every forms and classes
*/

class DataBaseThread : public QThread
{
    Q_OBJECT
public:
    ~DataBaseThread();
    void run();
    static DataBaseThread* getInstance(QObject *parent = nullptr);
    int databaseCommand = 0;
    QString devN;
    QString devA;
    QStringList devAdds;
    QString idToWrite;
    QString devAddrToWrite;
    QString addrToWrite;
    QString dataToWrite;
    QString dataFromReadDb;
    QString propertyA;
    QString propertyN;
    QString propertyT;
    QString propertyR;
    QString propertyU;
    QStringList coilsName;
    QStringList inputsName;
    QStringList brNames;
    QStringList brInputANames;
    QStringList brInputBNames;
    QStringList brTripBNames;
    QStringList brCloseBNames;

private:
    DataBaseThread(QObject *parent = nullptr);
    QString path = QDir::currentPath();
};

#endif // DATABASETHREAD_H
