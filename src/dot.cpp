#include "dot.h"

#include <QDebug>
Dot::Dot(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    count=0;
    num=0;
    // Set pixmap
    for(int i=0;i<15;++i){
        pix[i].setPixmap(pixmap);
        pix[i].setTransformOriginPoint(pix[i].boundingRect().width()/2,pix[i].boundingRect().height()/2);
    }
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;

    fixturedef.shape = &bodyshape;
    fixturedef.density = DOT_DENSITY;
    fixturedef.friction = DOT_FRICTION;
    fixturedef.restitution = DOT_RESTITUTION;
    g_body->SetAngularDamping(3);
    fixture=g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    for(int i=0;i<15;++i){
        scene->addItem(&pix[i]);
    }
}

void Dot::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Dot::paint(){
    count++;
    if(count==5 && num<15){
        pos = g_body->GetPosition();
        mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
        mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
        pix[num].setPos(mappedPoint);
        pix[num].resetTransform();
        pix[num].setRotation(-(g_body->GetAngle()*180/3.14159));
        count=0;
        num++;

    }
}

