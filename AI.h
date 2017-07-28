//
// Created by hosseinkh on 7/18/17.
//

#ifndef AGAR_AI_H
#define AGAR_AI_H
#include <QWidget>
#include <QtWidgets>
#include <QTcpSocket>
#include <QMediaPlayer>
#include <QtWidgets/QWidget>
#include <QHostAddress>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <vector>
class AiFoods{
public:
    int x;
    int y;
};
class AiMasses{
public:
    int x;
    int y;
};
class Aiopponents{
public:
    int x;
    int y;
    int r;
};
class point{
public:
    int x;
    int y;
};
class Ai{
public:
    int myradius;
    std::vector<AiFoods> foods;
    std::vector<AiMasses> masses;
    std::vector<Aiopponents>opps;
    point advance();
};
class AImode: public QWidget {
Q_OBJECT
public :
    AImode(int height, int width, QString *name, QHostAddress *, int c, QWidget *parent = 0);
    Ai ai;
    int f=33;
public slots:
    void reciveData();
    void sendData();
private:
    QTcpSocket *mysocket;
    //QMediaPlayer *myplayer;
    QHBoxLayout *qhb;
    QString *mymap;
    QColor *mycolor;
protected:
    void paintEvent(QPaintEvent *);

};

#endif //AGAR_AI_H
