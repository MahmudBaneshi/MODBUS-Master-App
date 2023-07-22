#ifndef LINEDIAGRAMSCENE_H
#define LINEDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QObject>

class LineDiagramScene : public QGraphicsScene
{
public:
    LineDiagramScene(QObject* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF origPoint;

};

#endif // LINEDIAGRAMSCENE_H
