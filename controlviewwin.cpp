#include "controlviewwin.h"
#include "ui_controlviewwin.h"

ControlViewWin::ControlViewWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlViewWin)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Window | Qt::WindowSystemMenuHint
                                | Qt::WindowMinimizeButtonHint
                                | Qt::WindowMaximizeButtonHint
                                | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    dbThread = DataBaseThread::getInstance(this);
    serThread = ConnectionThread::getInstance(this);

    scene = new LineDiagramScene(this);
    ui->graphicsView->setScene(scene);

    /*  draw feeder line  */
    const QColor color = Qt::white;
    bayLine = new QGraphicsLineItem();
    bayLine->setPen(QPen(Qt::white, 3, Qt::SolidLine));
    bayLine->setLine(0, 20, 200, 20);
    bayName = new QGraphicsTextItem("Bay0");
    bayName->setDefaultTextColor(color);
    bayName->setPos(200, 0);
    bay = new QGraphicsItemGroup();
    bay->addToGroup(bayLine);
    bay->addToGroup(bayName);
    bay->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(bay);


    /**/
    dbThread->databaseCommand = 15;
    dbThread->run();
    dbThread->wait();
    int j = dbThread->brNames.size();
    for (int i = 0; i < j; i++) {
        items.append(new BreakerItem());
        items[i]->brName = dbThread->brNames.at(i);
        items[i]->brInputAName = dbThread->brInputANames.at(i);
        items[i]->brInputBName = dbThread->brInputBNames.at(i);
        items[i]->brTripBName = dbThread->brTripBNames.at(i);
        items[i]->brCloseBName = dbThread->brCloseBNames.at(i);
        connect(items[i], SIGNAL(breakerPressed(QString, QString, QString, QString,
                                                QString, uint8_t)), this, SLOT(openBreakerCommandSlot(QString, QString, QString, QString,
                                                                                                      QString, uint8_t)));
        if(i == 0){
            items[i]->setPos(-50, 150);
            items[i]->breakerPosition = 0x01;
            items[i]->checkBreakerPosition();
            scene->addItem(items[i]);
            items[i]->setFlag(QGraphicsItem::ItemIsMovable);
            /*  line for breaker  */
            breakerLines.append(new QGraphicsLineItem());
            breakerLines[i]->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            breakerLines[i]->setLine(100, 20, 100, 200);
            scene->addItem(breakerLines[i]);
            breakerLines[i]->setFlag(QGraphicsItem::ItemIsMovable);
            /*  txt for breaker  */
            itemsTxt.append(new QGraphicsTextItem(items[i]->brName));
            itemsTxt[i]->setDefaultTextColor(color);
            itemsTxt[i]->setPos(110, 220);
            scene->addItem(itemsTxt[i]);
            itemsTxt[i]->setFlag(QGraphicsItem::ItemIsMovable);
            /*  end of feeder  */
            itemsEnd.append(new QGraphicsPixmapItem());
            itemsEnd[i]->setPixmap(pxEnd);
            itemsEnd[i]->setPos(-52, 310);
            scene->addItem(itemsEnd[i]);
            itemsEnd[i]->setFlag(QGraphicsItem::ItemIsMovable);
        }
        else {
            items[i]->setPos(-50 + i * 100, 150);
            items[i]->breakerPosition = 0x01;
            items[i]->checkBreakerPosition();
            scene->addItem(items[i]);
            items[i]->setFlag(QGraphicsItem::ItemIsMovable);
            /*  line for breaker  */
            breakerLines.append(new QGraphicsLineItem());
            breakerLines[i]->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            breakerLines[i]->setLine(100 + i * 100, 100, 100 + i * 100, 200);
            scene->addItem(breakerLines[i]);
            breakerLines[i]->setFlag(QGraphicsItem::ItemIsMovable);
            /*    */
            breakerLinesAdd.append(new QGraphicsLineItem());
            breakerLinesAdd[i - 1]->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            breakerLinesAdd[i - 1]->setLine(i * 100, 100, 100 + i * 100, 100);
            scene->addItem(breakerLinesAdd[i - 1]);
            breakerLinesAdd[i - 1]->setFlag(QGraphicsItem::ItemIsMovable);

            /*  txt for breaker  */
            itemsTxt.append(new QGraphicsTextItem(items[i]->brName));
            itemsTxt[i]->setDefaultTextColor(color);
            itemsTxt[i]->setPos(110 + i * 100, 220);
            scene->addItem(itemsTxt[i]);
            itemsTxt[i]->setFlag(QGraphicsItem::ItemIsMovable);
            /*  end of feeder  */
            itemsEnd.append(new QGraphicsPixmapItem());
            itemsEnd[i]->setPixmap(pxEnd);
            itemsEnd[i]->setPos(-52  + i * 100, 310);
            scene->addItem(itemsEnd[i]);
            itemsEnd[i]->setFlag(QGraphicsItem::ItemIsMovable);
        }
    }

}

ControlViewWin::~ControlViewWin()
{
    delete ui;
}

void ControlViewWin::openBreakerCommandSlot(QString brName , QString brInputAName, QString brInputBName, QString brTripBName,
                                            QString brCloseBName, uint8_t breakerPosition)
{
    #ifdef DEBUG_APP
    qDebug()<< brName<< brInputAName << brInputBName << brTripBName << brCloseBName << breakerPosition;
    #endif
    if(breakerPosition == 0x01){
        QMessageBox msg;
        msg.setText("Are you sure you want to close " + brName + " breaker?");
        msg.setIcon(QMessageBox::Question);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.exec();
    }
    else if(breakerPosition == 0x02){
        QMessageBox msg;
        msg.setText("Are you sure you want to open " + brName + " breaker?");
        msg.setIcon(QMessageBox::Question);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.exec();
    }
    else{
        QMessageBox msg;
        msg.setText("The breaker pos. is not valid");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }

}
