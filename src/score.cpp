#include "score.h"

Score::Score()
{
    score=0;
    setPlainText(QString("Score: ")+QString::number(score));
    QFont f;
    f.setFamily("Comic Sans MS");
    f.setBold(true);
    setScale(3);
    setFont(f);
}

void Score::increase(){
    score+=100;
    setPlainText(QString("Score: ")+QString::number(score));
}
