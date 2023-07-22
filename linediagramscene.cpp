#include "linediagramscene.h"

LineDiagramScene::LineDiagramScene(QObject *parent): QGraphicsScene(parent)
{

}


void LineDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void LineDiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void LineDiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}
