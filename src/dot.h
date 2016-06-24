#ifndef DOT_H
#define DOT_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

#define DOT_DENSITY 1.0f
#define DOT_FRICTION 0.2f
#define DOT_RESTITUTION 0.5f


class Dot:public GameItem
{
    Q_OBJECT
public:
    Dot(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    b2FixtureDef fixturedef;
    b2Fixture *fixture;
    b2Vec2 pos;
    QGraphicsPixmapItem pix[15];
    int count,num;
public slots:
    virtual void paint();
};

#endif // DOT_H
