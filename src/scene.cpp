#include "scene.h"
#include <QDebug>

Scene::Scene(QObject *parent)
{
    screenMode=0;
    checkMouse=0;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    checkMouse=1;
    x1=event->scenePos().x();
    y1=event->scenePos().y();
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    checkMouse=0;
    x2=event->scenePos().x();
    y2=event->scenePos().y();
    x=x2-x1;
    y=y1-y2;
    qDebug()<<x<<" x "<<y<<endl;
}
