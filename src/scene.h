#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Scene:public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent=0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    int x1,x2,y1,y2,x,y;
private:
    int checkMouse;
    int screenMode;
};

#endif // SCENE_H
