//
// Created by hosseinkh on 7/13/17.
//

#ifndef AGAR_SPECTATOR_H
#define AGAR_SPECTATOR_H
#include <QWidget>
#include <QtWidgets>
#include <QTcpSocket>
#include <QMediaPlayer>
#include <QtWidgets/QWidget>
#include <QHostAddress>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
class Smode: public QWidget {
    Q_OBJECT
public :
    Smode(int height, int width, QString *name, QHostAddress *, int c,int p, QWidget *parent = 0);
public slots:
    void reciveData();
private:
    QTcpSocket *mysocket;
    //QMediaPlayer *myplayer;
    QHBoxLayout *qhb;
    QString *mymap;
    QColor *mycolor;
protected:
    void paintEvent(QPaintEvent *);

};
#endif //AGAR_SPECTATOR_H
