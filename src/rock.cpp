#include "rock.h"

Rock::Rock(int m,float x,float y,float w,float h,QTimer *timer,QPixmap pixmap,b2World *world,QGraphicsScene *scene):GameItem(world)
{
    hit=0;
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;  //???
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(w/2.0f,h/2.0f);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    if(m==1) fixturedef.density = ROCK_DENSITY1;
    if(m==2) fixturedef.density = ROCK_DENSITY2;
    if(m==3) fixturedef.density = ROCK_DENSITY3;
    fixturedef.friction = ROCK_FRICTION;
    fixturedef.restitution = ROCK_RESTITUTION;
 //   g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetLinearVelocity(b2Vec2(0,0));
    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Rock::paint()
{
    b2Vec2 pos = g_body->GetPosition();
//    std::cout << g_body->GetPosition().x << std::endl;
//    std::cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height()+30);   //??
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
}

void Rock::collide(){
    float x = g_body->GetPosition().x;
    float y = g_body->GetPosition().y;

    if(x > 32.0 || x<0.0) delete this;
    if(y<0.0) delete this;

}
