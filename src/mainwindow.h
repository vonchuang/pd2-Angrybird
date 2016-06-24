#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <target.h>
#include <score.h>
#include <rock.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void createobticle();

    int x,x1,x2,y,y1,y2,x3,y3,xb,yb;
    int xt1,xt2,xt3,xt4,yt1,yt2,yt3,yt4;
    int checkMouse;
    int birdMode;
    int ck;
    float xt,yt,xd,yd;
    Land *land1;
    Land *land2;
    Bird *bird;
    Bird *bird2;
    Bird *bird3;
    Bird *win;
    Score *score;
    Target *target1;
    Target *target2;
    Target *target3;
    Target *target4;
    Rock *rock[16];
    int birdNumber;
    int ScreenMode;
    int btn_w,btn_h;
    int check,playtimes;
    int checkBird23;
    float vx,vy;
    QPixmap birtmp;
    QPixmap dot;
    QGraphicsPixmapItem *dots[15];
    QGraphicsPixmapItem *birdtmp;
    QGraphicsPixmapItem *tool;
    QGraphicsPixmapItem *restart;
    QGraphicsPixmapItem *exit;
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void birdHit();
    void endPage();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
};

#endif // MAINWINDOW_H
