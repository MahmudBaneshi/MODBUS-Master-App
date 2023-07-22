#ifndef BREAKERITEM_H
#define BREAKERITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>

class BreakerItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BreakerItem();
    bool Pressed;
    QString brName;
    QString brInputAName;
    QString brInputBName;
    QString brTripBName;
    QString brCloseBName;
    uint8_t breakerPosition = 0x00;   /*  this holds the breaker position open : 0x01, close : 0x02, notValid: 0x00 */
    void checkBreakerPosition(void);

signals:
    void breakerPressed(QString brName , QString brInputAName, QString brInputBName, QString brTripBName,
                        QString brCloseBName, uint8_t breakerPosition);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QPixmap pxOpen = QPixmap(":/imgs/normally-open-contact.png");
    QPixmap pxClose = QPixmap(":/imgs/normally-close-contact.png");
    QPixmap pxUnknown = QPixmap(":/imgs/normally-unknown-contact.png.svg");
};

#endif // BREAKERITEM_H
