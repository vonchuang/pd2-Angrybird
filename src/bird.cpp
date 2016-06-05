#include "bird.h"
#include <QDebug>
Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    count=0;
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
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
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    fixture=g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));
    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Bird::collide(){
    count++;
    float x = g_body->GetPosition().x;
    float y = g_body->GetPosition().y;

    if(x > 32.0 || x<0.0){ emit endGame(); delete this;}
    if(y<0.0){ emit endGame(); delete this;}
    if(count==300){ emit endGame();}
    if(count==360) delete this;

}

