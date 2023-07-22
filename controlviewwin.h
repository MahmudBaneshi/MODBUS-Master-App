#ifndef CONTROLVIEWWIN_H
#define CONTROLVIEWWIN_H

#include <QDialog>
#include "databasethread.h"
#include "connectionthread.h"
#include "linediagramscene.h"
#include "breakeritem.h"

namespace Ui {
class ControlViewWin;
}

class ControlViewWin : public QDialog
{
    Q_OBJECT

public:
    explicit ControlViewWin(QWidget *parent = nullptr);
    ~ControlViewWin();

public slots:
    void openBreakerCommandSlot(QString brName , QString brInputAName, QString brInputBName, QString brTripBName,
                                QString brCloseBName, uint8_t breakerPosition);

private:
    Ui::ControlViewWin *ui;
    DataBaseThread *dbThread;
    ConnectionThread *serThread;
    LineDiagramScene *scene;
    QGraphicsTextItem *bayName;
    QGraphicsLineItem *bayLine;
    QGraphicsItemGroup *bay;
    QList <BreakerItem*> items;
    QList <QGraphicsTextItem*> itemsTxt;
    QList <QGraphicsPixmapItem*> itemsEnd;
    QList <QGraphicsLineItem*> breakerLines;
    QList <QGraphicsLineItem*> breakerLinesAdd;
    QPixmap pxEnd = QPixmap(":/imgs/from-link-vertical.png");
};

#endif // CONTROLVIEWWIN_H
