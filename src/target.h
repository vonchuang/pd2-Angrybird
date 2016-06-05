#ifndef TARGET_H
#define TARGET_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define TARGET_DENSITY 5.0f
#define TARGET_FRICTION 0.2f
#define TARGET_RESTITUTION 0.5f

class Target:public GameItem
{
public:
    Target(float x,float y,float radius,QTimer *timer,QPixmap pixmap,b2World *world,QGraphicsScene *scene);
    int hit;
};

#endif // TARGET_H
