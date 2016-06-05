#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsScene>
#include <QFont>

class Score:public QGraphicsTextItem
{
    Q_OBJECT
public:
    Score();
public slots:
    void increase();
private:
    int score;
};

#endif // SCORE_H
