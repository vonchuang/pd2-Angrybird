#ifndef ROCK_H
#define ROCK_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define ROCK_DENSITY1 5.0f
#define ROCK_DENSITY2 15.0f
#define ROCK_DENSITY3 10.0f
#define ROCK_FRICTION 0.2f
#define ROCK_RESTITUTION 0.5f

class Rock:public GameItem
{
public:
    Rock(int m,float x,float y,float w,float h,QTimer *timer,QPixmap pixmap,b2World *world,QGraphicsScene *scene);
    int hit;

public slots:
    void paint();
    virtual void collide();

};

#endif // ROCK_H
