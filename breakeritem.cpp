#include "breakeritem.h"

BreakerItem::BreakerItem()
{
    Pressed = false;
    setPixmap(pxUnknown);
}

void BreakerItem::checkBreakerPosition()
{
    if(breakerPosition == 0x01){
        setPixmap(pxOpen);
    }
    else if (breakerPosition == 0x02){
        setPixmap(pxClose);
    }
    else {
        setPixmap(pxUnknown);
    }
}

void BreakerItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void BreakerItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    emit breakerPressed(brName , brInputAName, brInputBName, brTripBName, brCloseBName, breakerPosition);
}
