#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QObject>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "shareddata.h"
#include "databasethread.h"

enum mdResults {COMMAND_SUCCESSFUL = 1, COMMAND_NOT_SUCCESSFUL};
#define POLYNUMERIC 0xA001
/*
 *   this is based on singelton design pattern
 *   it can be used in every forms and classes
*/


class ConnectionThread : public QThread
{
public:
    ~ConnectionThread();
    void run();
    static ConnectionThread* getInstance(QObject *parent = nullptr);
    int serialCommand = 0;
    uint8_t devAddressToWrite = 0;
    uint16_t addressToWrite = 0;
    uint16_t dataToWrite = 0;
    QList<uint16_t> dataFromRead;
    uint16_t numOfPoints = 0;
    QString idToWriteSer;
    int commandResult = 0;
private:
    ConnectionThread(QObject *parent = nullptr);
    QSerialPort* serialPort;
    QByteArray sendData;
    char sendArray[1024];
    int serialError;
    unsigned int calculate_CRC(QByteArray DataIn, int l);
    uint16_t generate_CRC(char *DataIn, int l);
    uint16_t MODBUS_CRC16_v1(char *buf, unsigned int len);
    DataBaseThread *dbThread;
};

#endif // CONNECTIONTHREAD_H
