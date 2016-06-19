#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    checkMouse=0;
    birdNumber=0;
    ScreenMode=0;
    check=0;
    playtimes=0;
    birdMode=0;
    checkBird23=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    if(check==1){
        for(int i=0;i<itemList.size();++i){

        }
        itemList.clear();
        scene->removeItem(restart);
        scene->removeItem(exit);
        scene->addItem(birdtmp);
        scene->addItem(tool);
        itemList.clear();
        //bird,obticle,target
        birdNumber=0;
        ScreenMode=0;
        checkBird23=0;
        target1->hit=0;
//        qDebug()<<x<<" hit=0 "<<y<<endl;
    }
    if(playtimes==0){
        // Timer
        connect(&timer,SIGNAL(timeout()),this,SLOT(birdHit()));
        connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
        connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
        timer.start(100/6);
    }
// Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    QImage bg;
    bg.load(":/img/bg.jpg");
    bg=bg.scaled(960,540);
    ui->graphicsView->scene()->setBackgroundBrush(bg);
    //bg-bird
    birdtmp=new QGraphicsPixmapItem();
    QPixmap bir;
    bir.load(":/img/bird1.png");
    bir=bir.scaled(50,50);
    birdtmp->setPixmap(bir);
    birdtmp->setPos(205,360);
    ui->graphicsView->scene()->addItem(birdtmp);
    //bg-tool
    tool=new QGraphicsPixmapItem();
    QPixmap tol;
    tol.load(":/img/tool.png");
    tol=tol.scaled(50,70);
    tool->setPixmap(tol);
    tool->setPos(210,380);
    ui->graphicsView->scene()->addItem(tool);
    //score
    score=new Score();
    this->scene->addItem(score);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));

    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
//    qDebug()<<size().width()<<" "<<size().height()<<endl;
    // Create ground (You can edit here)

    land1=new Land(3,1.5,5,3,QPixmap(":/img/GROUND.png").scaled(225,height()/6.0),world,scene);
    itemList.push_back(land1);
    land2=new Land(25,1.5,20,3,QPixmap(":/img/GROUND.png").scaled(600,height()/6.0),world,scene);
    itemList.push_back(land2);

    //create target
    target1=new Target(20.2f,6.4f,0.1f,&timer,QPixmap(":/img/target1.png").scaled(40,40),world,scene);
    itemList.push_back(target1);

    target2=new Target(26.0f,5.8f,0.1f,&timer,QPixmap(":/img/target1.png").scaled(40,40),world,scene);
    itemList.push_back(target1);

    target3=new Target(22.0f,5.0f,0.1f,&timer,QPixmap(":/img/target2.png").scaled(40,40),world,scene);
    itemList.push_back(target1);

    target4=new Target(29.0f,5.0f,0.1f,&timer,QPixmap(":/img/target2.png").scaled(40,40),world,scene);
    itemList.push_back(target1);

    //create obticle
    createobticle();

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    QMouseEvent *mouse=static_cast<QMouseEvent*>(event);
    QKeyEvent *key=static_cast<QKeyEvent*>(event);

    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        // TODO : add your code here
        checkMouse=1;
        x1=mouse->pos().x();
        y1=mouse->pos().y();
        //std::cout << "Press !" << std::endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        // TODO : add your code here
        if(checkMouse==1 && ScreenMode==0){
            x3=mouse->pos().x();
            y3=mouse->pos().y();
            xb=x1-x3;
            yb=y3-y1;
            if(xb>30) xb=30;
            if(yb>30) yb=30;
            if(xb<-30) xb=-30;
            if(yb<-30) yb=-30;
            birdtmp->setPos(205-xb,360+yb);
        }else if(checkMouse==0 && ScreenMode==0){
            birdtmp->setPos(205,360);
        }
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        // TODO : add your code here
        //std::cout << "Release !" << std::endl ;
        if(ScreenMode==0){
            if(checkMouse==1){
                if(check==0){
                    if(birdNumber<4){
                        if(birdNumber>0) birdMode=1;
                        if(birdNumber==2) world->SetGravity(b2Vec2(0.0f, -9.8f));
                        x2=mouse->pos().x();
                        y2=mouse->pos().y();
                        x=x1-x2;
                        y=y2-y1;
               //         qDebug()<<x<<" x "<<y<<endl;
                        vx=x/10.0;
                        vy=y/10.0;
                    //bird mode
                        if(birdNumber==0){
                            bird = new Bird(7.0f,5.0f,0.27f,&timer,QPixmap(":/img/bird1.png").scaled(50,50),world,scene);
                            birtmp.load(":/img/bird2.png");
                            birtmp=birtmp.scaled(50,50);
                            birdtmp->setPixmap(birtmp);
                        }
                        if(birdNumber==1){
                            bird = new Bird(7.0f,5.0f,0.27f,&timer,QPixmap(":/img/bird2.png").scaled(50,50),world,scene);
                            birtmp.load(":/img/bird3.png");
                            birtmp=birtmp.scaled(50,50);
                            birdtmp->setPixmap(birtmp);
                        }
                        if(birdNumber==2){
                            bird = new Bird(7.0f,5.0f,0.27f,&timer,QPixmap(":/img/bird3.png").scaled(50,50),world,scene);
                            birtmp.load(":/img/bird4.png");
                            birtmp=birtmp.scaled(50,50);
                            birdtmp->setPixmap(birtmp);
                        }
                        if(birdNumber==3){
                            scene->removeItem(birdtmp);
                            bird = new Bird(7.0f,5.0f,0.27f,&timer,QPixmap(":/img/bird4.png").scaled(50,50),world,scene);
                            connect(bird,SIGNAL(endGame()),this,SLOT(endPage()));
                        }
                        // Setting the Velocity
                        itemList.push_back(bird);
                        bird->setLinearVelocity(b2Vec2(vx,vy));
                   //     std::cout <<vx<< " v " <<vy<< std::endl ;

                        birdNumber++;
                        checkMouse=0;
                    }

                }else if(check==1){
                    birdNumber=0;
                    check=0;
                    qDebug()<<x<<" check=0 "<<y<<endl;
                }
            }
        }else if(ScreenMode==1){
            qDebug()<<"btn"<<endl;
            //press restart
            if(mouse->pos().x() > restart->pos().x() && mouse->pos().x() <= restart->pos().x()+btn_w){
                if(mouse->pos().y() > restart->pos().y() && mouse->pos().y() <= restart->pos().y()+btn_h){
                    //restartGame();
                    check=1;
                    QShowEvent *a;
                    showEvent(a);
                    qDebug()<<"press restart"<<endl;
                }
            }
            //press exit
            if(mouse->pos().x()>exit->pos().x() && mouse->pos().x()<=exit->pos().x()+btn_w){
                if(mouse->pos().y()>exit->pos().y() && mouse->pos().y()<=exit->pos().y()+btn_h){
                    qDebug()<<"press exit"<<endl;
                    emit quitGame();
                }
            }

        }
    }

    //bird mode
    if(birdMode==1 && birdNumber==2 && key->key()==0x5a){
        world->SetGravity(b2Vec2(0.0f, -50.0f));
        checkMouse=0;
        qDebug()<<"bird2"<<endl;
        birdMode=0;
    }

    if(birdMode==1 && birdNumber==3 && key->key()==0x5a){
        if(vx>0) vx=vx*4;
        else if (vx<0) vx=vx*(-4);
 //       if(vy>0) vy=vy*4;
 //       else if(vy<0) vy=vy*(-4);

        bird->setLinearVelocity(b2Vec2(vx,vy));
        checkMouse=0;
        birdMode=0;
        qDebug()<<"bird3"<<endl;
    }

    if(birdMode==1 && birdNumber==4 && key->key()==0x5a){

        bird2 = new Bird(bird->mappedPoint.x()/30.0f,18.0f-bird->mappedPoint.y()/30.0f,0.27f,&timer,QPixmap(":/img/bird4.png").scaled(50,50),world,scene);
        bird3 = new Bird(bird->mappedPoint.x()/30.0f,18.0f-bird->mappedPoint.y()/30.0f,0.27f,&timer,QPixmap(":/img/bird4.png").scaled(50,50),world,scene);
        bird2->setLinearVelocity(b2Vec2(vx,vy+10));
        bird3->setLinearVelocity(b2Vec2(vx,vy-5));
        checkBird23=1;
        checkMouse=0;
        qDebug()<<"bird4"<<endl;
        birdMode=0;
    }

    return false;
}


void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::birdHit(){
   // qDebug()<<"hit"<<endl;
    if(birdNumber>0 && ScreenMode==0){
        //target1
        if(target1->hit==0){
            xt1=bird->mappedPoint.x()-target1->mappedPoint.x();
            yt1=bird->mappedPoint.y()-target1->mappedPoint.y();
            if(xt1>-20 && xt1<20 && yt1>-15 && yt1<15){
                score->increase();
                target1->hit=1;
            }
            if(checkBird23==1){
                if(xt1>-20 && xt1<20 && yt1>-15 && yt1<15){
                    score->increase();
                    target1->hit=1;
                }
                if(xt1>-20 && xt1<20 && yt1>-15 && yt1<15){
                    score->increase();
                    target1->hit=1;
                }
            }

            if(target1->mappedPoint.y()>400){
                score->increase();
                target1->hit=1;
                qDebug()<<"hit"<<endl;
            }
        }
        //target2
        if(target2->hit==0){
            xt2=bird->mappedPoint.x()-target2->mappedPoint.x();
            yt2=bird->mappedPoint.y()-target2->mappedPoint.y();
            if(xt2>-20 && xt2<20 && yt2>-15 && yt2<15){
                score->increase();
                target2->hit=1;
            }
            if(checkBird23==1){
                if(xt2>-20 && xt2<20 && yt2>-15 && yt2<15){
                    score->increase();
                    target2->hit=1;
                }
                if(xt2>-20 && xt2<20 && yt2>-15 && yt2<15){
                    score->increase();
                    target2->hit=1;
                }
            }

            if(target2->mappedPoint.y()>400){
                score->increase();
                target2->hit=1;
                qDebug()<<"hit"<<endl;
            }
        }
        //target3
        if(target3->hit==0){
            xt3=bird->mappedPoint.x()-target3->mappedPoint.x();
            yt3=bird->mappedPoint.y()-target3->mappedPoint.y();
            if(xt3>-20 && xt3<20 && yt3>-15 && yt3<15){
                score->increase();
                score->increase();
                target3->hit=1;
            }
            if(checkBird23==1){
                if(xt3>-20 && xt3<20 && yt3>-15 && yt3<15){
                    score->increase();
                    score->increase();
                    target3->hit=1;
                }
                if(xt3>-20 && xt3<20 && yt3>-15 && yt3<15){
                    score->increase();
                    score->increase();
                    target3->hit=1;
                }
            }
        }
        //target4
        if(target4->hit==0){
            xt4=bird->mappedPoint.x()-target4->mappedPoint.x();
            yt4=bird->mappedPoint.y()-target4->mappedPoint.y();
            if(xt4>-20 && xt4<20 && yt4>-15 && yt4<15){
                score->increase();
                score->increase();
                target4->hit=1;
            }
            if(checkBird23==1){
                if(xt4>-20 && xt4<20 && yt4>-15 && yt4<15){
                    score->increase();
                    score->increase();
                    target4->hit=1;
                }
                if(xt4>-20 && xt4<20 && yt4>-15 && yt4<15){
                    score->increase();
                    score->increase();
                    target4->hit=1;
                }
            }
        }

    }
}
//tbc
void MainWindow::createobticle(){
    //create rock
    rock[0]=new Rock(2,19.4f,4.6f,0.3f,1.4f,&timer,QPixmap(":/img/obj2.png").scaled(13.5,63),world,scene);
    itemList.push_back(rock[0]);
    rock[1]=new Rock(2,20.0f,4.6f,0.3f,0.9f,&timer,QPixmap(":/img/obj2.png").scaled(13.5,40.5),world,scene);
    itemList.push_back(rock[1]);
    rock[2]=new Rock(2,20.6f,4.6f,0.3f,0.9f,&timer,QPixmap(":/img/obj2.png").scaled(13.5,45),world,scene);
    itemList.push_back(rock[2]);
    rock[3]=new Rock(2,20.0f,5.5f,0.9f,0.5f,&timer,QPixmap(":/img/obj2.png").scaled(40.5,22.5),world,scene);
    itemList.push_back(rock[3]);
    rock[4]=new Rock(2,20.0f,6.0f,2.0f,0.3f,&timer,QPixmap(":/img/obj2.png").scaled(90,13.5),world,scene);
    itemList.push_back(rock[4]);    //x->??
    rock[14]=new Rock(2,19.4f,6.4f,0.9f,0.5f,&timer,QPixmap(":/img/obj2.png").scaled(40.5,22.5),world,scene);
    itemList.push_back(rock[14]);

    //tbc

    rock[5]=new Rock(2,24.5f,4.6f,0.6f,0.3f,&timer,QPixmap(":/img/obj2.png").scaled(27,13.5),world,scene);
    itemList.push_back(rock[5]);
    rock[6]=new Rock(3,24.5f,4.9f,0.6f,0.6f,&timer,QPixmap(":/img/obj3.png").scaled(27,20),world,scene);
    itemList.push_back(rock[6]);

    rock[7]=new Rock(2,26.0f,4.6f,0.6f,0.3f,&timer,QPixmap(":/img/obj2.png").scaled(27,13.5),world,scene);
    itemList.push_back(rock[7]);
    rock[8]=new Rock(3,26.0f,4.9f,0.6f,0.6f,&timer,QPixmap(":/img/obj3.png").scaled(27,20),world,scene);
    itemList.push_back(rock[8]);

    rock[9]=new Rock(2,27.0f,4.6f,0.6f,0.3f,&timer,QPixmap(":/img/obj2.png").scaled(27,13.5),world,scene);
    itemList.push_back(rock[9]);
    rock[10]=new Rock(3,27.0f,4.9f,0.6f,0.6f,&timer,QPixmap(":/img/obj3.png").scaled(27,20),world,scene);
    itemList.push_back(rock[10]);

    rock[11]=new Rock(1,25.8f,5.5f,3.0f,0.3f,&timer,QPixmap(":/img/obj1.png").scaled(135,13.5),world,scene);
    itemList.push_back(rock[11]);
    rock[12]=new Rock(1,25.0f,5.8f,0.5f,0.5f,&timer,QPixmap(":/img/obj1.png").scaled(22.5,22.5),world,scene);
    itemList.push_back(rock[12]);
    rock[13]=new Rock(1,27.0f,5.8f,0.5f,0.5f,&timer,QPixmap(":/img/obj1.png").scaled(22.5,22.5),world,scene);
    itemList.push_back(rock[13]);

    rock[15]=new Rock(2,31.0f,4.6f,1.0f,2.0f,&timer,QPixmap(":/img/obj2.png").scaled(45,90),world,scene);
    itemList.push_back(rock[15]);

}

void MainWindow::endPage(){
    ScreenMode=1;
    playtimes=1;
    //exit
    exit=new QGraphicsPixmapItem();
    QPixmap ext;
    ext.load(":/img/exit.png");
    ext=ext.scaled((ext.width()*3)/2,(ext.height()*3)/2,Qt::KeepAspectRatio);
    exit->setPixmap(ext);
    exit->setPos(600,390);
    scene->addItem(exit);
    //restart
    restart=new QGraphicsPixmapItem();
    QPixmap rst;
    rst.load(":/img/restart.png");
    rst=rst.scaled((rst.width()*3)/2,(rst.height()*3)/2,Qt::KeepAspectRatio);
    restart->setPixmap(rst);
    restart->setPos(350,390);
    scene->addItem(restart);

    btn_w=(rst.width()*3)/2-60;
    btn_h=(rst.height()*3)/2-30;

    QImage bg2;
    bg2.load(":/img/bg2.jpg");
    bg2=bg2.scaled(960,540);
    ui->graphicsView->scene()->setBackgroundBrush(bg2);
    scene->removeItem(birdtmp);
    scene->removeItem(tool);
    score->setPos(450,250);
    score->setScale(5);
 //   qDebug()<<"endPage"<<endl;
    disconnect(bird,SIGNAL(endGame()),this,SLOT(endPage()));
    delete land1;
    delete land2;
    delete target1;
    delete target2;
    delete target3;
    delete target4;

}
