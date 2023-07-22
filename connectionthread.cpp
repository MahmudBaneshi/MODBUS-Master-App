#include "connectionthread.h"

QString COMPortName;
QString COMPortParity;
QString COMPortBaud;

ConnectionThread::ConnectionThread(QObject *parent) : QThread(parent)
{
    dbThread = DataBaseThread::getInstance(this);
}

ConnectionThread::~ConnectionThread()
{

}

void ConnectionThread::run()
{
    /*  if command is successful this var. will be COMMAND_SUCCESSFUL in the end  */
    commandResult = COMMAND_NOT_SUCCESSFUL;
    if(serialCommand == 1){           /*  Send Read Command  */
        /*  SLAVE ADDr.
         *  FUN 0x03
         *  ADDR. HI
         *  ADDR. LO
         *  # POINTS HI
         *  # POINTS LO
         *  CRC HI
         *  CRC LO
        */
        #ifdef DEBUG_APP
        qDebug()<< COMPortParity << COMPortBaud << COMPortName;
        #endif
        serialPort = new QSerialPort();
        serialPort->setPortName(COMPortName);
        serialPort->close();
        serialPort->setBaudRate(COMPortBaud.toInt());
        serialPort->setDataBits(QSerialPort::Data8);
        if(COMPortParity == "ODD"){
            serialPort->setParity(QSerialPort::OddParity);
        }
        if(COMPortParity == "EVEN"){
            serialPort->setParity(QSerialPort::EvenParity);
        }
        else{
            serialPort->setParity(QSerialPort::NoParity);
        }
        serialPort->setStopBits(QSerialPort::OneStop);
        if(serialPort->open(QIODevice::ReadWrite)){
            #ifdef DEBUG_APP
            qDebug()<< "PORT OPENED " << devAddressToWrite << addressToWrite << dataToWrite;
            #endif
            sendArray[0] = devAddressToWrite;
            sendArray[1] = 0x03;
            sendArray[2] = ((uint8_t)(addressToWrite >> 8));
            sendArray[3] = ((uint8_t)(addressToWrite & 0x00FF));
            sendArray[4] = ((uint8_t)(numOfPoints >> 8));
            sendArray[5] = ((uint8_t)(numOfPoints & 0x00FF));
            uint16_t res_crc = MODBUS_CRC16_v1(sendArray, 6);
            sendArray[6] = ((uint8_t)(res_crc & 0x00FF));
            sendArray[7] = ((uint8_t)((res_crc & 0xFF00) >> 8));
            #ifdef DEBUG_APP
            qDebug()<< "CRC : " << res_crc;
            qDebug()<< "SEND DATA : " << QByteArray(sendArray, 8).toHex().constData();
            #endif
            serialPort->write(sendArray, 8);
            QByteArray receiveData;
            receiveData.clear();
            while (serialPort->waitForReadyRead(2000)) {
                if(serialPort->bytesAvailable()){
                    receiveData.append(serialPort->readAll());
                }
            }
            #ifdef DEBUG_APP
            qDebug()<< "Recieced Data : " << receiveData.toHex().constData();
            #endif
            dataFromRead.clear();
            if(receiveData.size() > 0){
                uint8_t tmp_1 = receiveData.at(0);
                if(tmp_1 == devAddressToWrite){
                    char *data = new char[numOfPoints * 2 + 5];
                    for(int j = 0; j < (numOfPoints * 2 + 5); j++){
                        data[j] = receiveData.at(j);
                    }
                    #ifdef DEBUG_APP
                    qDebug()<< "DATA : " << QByteArray(data, 8).toHex().constData() << "SIZE : " << receiveData.size();
                    #endif
                    uint16_t r_crc = MODBUS_CRC16_v1(data, 3 + numOfPoints * 2);
                    uint16_t tmp_crc = (uint16_t)data[4 + numOfPoints * 2];
                    tmp_crc = tmp_crc << 8;
                    tmp_crc &= 0xFF00;
                    tmp_crc |= (0x00FF & (uint16_t)data[3 + numOfPoints * 2]);
                    #ifdef DEBUG_APP
                    qDebug()<< "Recieced CRC : " << r_crc << tmp_crc;
                    #endif
                    if(tmp_crc == r_crc){
                        #ifdef DEBUG_APP
                        qDebug()<< "Recieced CRC : " << r_crc;
                        #endif
                        commandResult = COMMAND_SUCCESSFUL;
                        for(uint16_t k = 0; k < numOfPoints * 2; k += 2){
                            uint16_t tmp = (uint16_t)data[3 + k];
                            tmp = tmp << 8;
                            tmp &= 0xFF00;
                            tmp |= (0x00FF & (uint16_t)data[4 + k]);
                            dataFromRead.append(tmp);
                            dbThread->databaseCommand = 10;
                            dbThread->idToWrite = idToWriteSer;
                            dbThread->dataFromReadDb = QString::number(dataFromRead.last());
                            dbThread->run();
                            dbThread->wait();
                        }
                    }
                    delete [] data;
                }
            }
        }
        else {
            #ifdef DEBUG_APP
            qDebug()<< serialPort->error();
            #endif
        }
        /*  SLAVE ADDr.
         *  FUN 0x03
         *  BYTE COUNT
         *  DATA HI
         *  DATA LO
         *  ..
         *  ..
         *  CRC HI
         *  CRC LO
        */
        delete serialPort;
    }
    if(serialCommand == 2){           /*  Send Write Command (One Reg)  */
        /*  SLAVE ADDr.
         *  FUN 0x06
         *  ADDR. HI
         *  ADDR. LO
         *  DATA HI
         *  DATA LO
         *  CRC HI
         *  CRC LO
        */
        #ifdef DEBUG_APP
        qDebug()<< COMPortParity << COMPortBaud << COMPortName;
        #endif
        serialPort = new QSerialPort();
        serialPort->setPortName(COMPortName);
        serialPort->close();
        serialPort->setBaudRate(COMPortBaud.toInt());
        serialPort->setDataBits(QSerialPort::Data8);
        if(COMPortParity == "ODD"){
            serialPort->setParity(QSerialPort::OddParity);
        }
        if(COMPortParity == "EVEN"){
            serialPort->setParity(QSerialPort::EvenParity);
        }
        else{
            serialPort->setParity(QSerialPort::NoParity);
        }
        serialPort->setStopBits(QSerialPort::OneStop);
        if(serialPort->open(QIODevice::ReadWrite)){
            #ifdef DEBUG_APP
            qDebug()<< "PORT OPENED " << devAddressToWrite << addressToWrite << dataToWrite;
            #endif
            sendArray[0] = devAddressToWrite;
            sendArray[1] = 0x06;
            sendArray[2] = ((uint8_t)(addressToWrite >> 8));
            sendArray[3] = ((uint8_t)(addressToWrite & 0x00FF));
            sendArray[4] = ((uint8_t)(dataToWrite >> 8));
            sendArray[5] = ((uint8_t)(dataToWrite & 0x00FF));
            uint16_t res_crc = MODBUS_CRC16_v1(sendArray, 6);
            sendArray[6] = ((uint8_t)(res_crc & 0x00FF));
            sendArray[7] = ((uint8_t)((res_crc & 0xFF00) >> 8));
            #ifdef DEBUG_APP
            qDebug()<< "CRC : " << res_crc;
            qDebug()<< "SEND DATA : " << QByteArray(sendArray, 8).toHex().constData();
            #endif
            serialPort->write(sendArray, 8);
            QByteArray receiveData;
            receiveData.clear();
            while (serialPort->waitForReadyRead(2000)) {
                if(serialPort->bytesAvailable()){
                    receiveData.append(serialPort->readAll());
                }
            }
            #ifdef DEBUG_APP
            qDebug()<< receiveData.toHex().constData();
            #endif
            if(strcmp(receiveData.toHex().constData(), QByteArray(sendArray, 8).toHex().constData()) == 0){
                commandResult = COMMAND_SUCCESSFUL;
            }
            else {
                commandResult = COMMAND_NOT_SUCCESSFUL;
            }

        }
        else {
            #ifdef DEBUG_APP
            qDebug()<< serialPort->error();
            #endif
        }
        /*  SLAVE ADDr.
         *  FUN 0x06
         *  ADDR. HI
         *  ADDR. LO
         *  DATA HI
         *  DATA LO
         *  CRC HI
         *  CRC LO
        */
        delete serialPort;
    }
    if(serialCommand == 3){           /*  Send Write Command (Multiple Regs)  */
        /*  SLAVE ADDr.
         *  FUN 0x10
         *  ADDR. HI
         *  ADDR. LO
         *  NUMBER HI
         *  NUMBER LO
         *  BYTE COUNT
         *  DATA HI
         *  DATA LO
         *  ..
         *  ..
         *  CRC HI
         *  CRC LO
        */


        /*  SLAVE ADDr.
         *  FUN 0x10
         *  ADDR. HI
         *  ADDR. LO
         *  NUMBER HI
         *  NUMBER LO
         *  CRC HI
         *  CRC LO
        */
}
    if(serialCommand == 4){           /*  Read COILS  */

    }
    if(serialCommand == 5){           /*  Read INPUT STATUS  */

    }
    if(serialCommand == 6){           /*  Force Single COIL  */

    }
}
ConnectionThread *ConnectionThread::getInstance(QObject *parent)
{
    static ConnectionThread *instance = nullptr;
    if(instance == nullptr){
        instance = new ConnectionThread(parent);
    }
    return instance;
}

uint16_t ConnectionThread::generate_CRC(char *DataIn, int l)
{
    uint16_t tmp_CRC;
    tmp_CRC = 0xFFFF;
    for(int i1=0; i1< l; i1++){
        tmp_CRC ^= DataIn[i1];
        for(int j1=0; j1<=7; j1++){
            if( tmp_CRC & 1 ){
                tmp_CRC >>= 1;
                tmp_CRC ^= POLYNUMERIC;
            }else{
                tmp_CRC >>= 1;
            }
        }
    }
    return tmp_CRC;
}
unsigned int ConnectionThread::calculate_CRC(QByteArray DataIn, int l)
{
    unsigned int calculated_CRC = 0xFFFF;
    /*  check for check sum match!  */
    for(int i = 0;i < l;i++)
    {
        calculated_CRC ^= DataIn[i];
        for(int j = 0; j <= 7; j++)
        {
            if( calculated_CRC & 1 )
            {
                calculated_CRC >>= 1;
                calculated_CRC ^= POLYNUMERIC;
            }
            else
            {
                calculated_CRC >>= 1;
            }
        }
    }
    return calculated_CRC;
}
uint16_t ConnectionThread::MODBUS_CRC16_v1(char *buf, unsigned int len )
{
    #ifdef CRC_METHOD_1
    uint16_t crc = 0xFFFF;
    unsigned int i = 0;
    char bit = 0;

    for( i = 0; i < len; i++ )
    {
        crc ^= buf[i];

        for( bit = 0; bit < 8; bit++ )
        {
            if( crc & 0x0001 )
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
    #endif
    static const uint16_t table[256] = {
        0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
        0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
        0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
        0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
        0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
        0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
        0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
        0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
        0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
        0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
        0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
        0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
        0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
        0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
        0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
        0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
        0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
        0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
        0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
        0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
        0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
        0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
        0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
        0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
        0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
        0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
        0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
        0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
        0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
        0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
        0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 };

        uint8_t xor1 = 0;
        uint16_t crc = 0xFFFF;

        while( len-- )
        {
            xor1 = (*buf++) ^ crc;
            crc >>= 8;
            crc ^= table[xor1];
        }

        return crc;
}
