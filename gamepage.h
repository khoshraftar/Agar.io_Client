//
// Created by hosseinkh on 6/29/17.
//

#ifndef AGAR_GAMEPAGE_H
#define AGAR_GAMEPAGE_H
#include <QWidget>
#include <QtWidgets>
#include <QTcpSocket>
#include <QMediaPlayer>
#include <QtWidgets/QWidget>
#include <QHostAddress>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
class game : public QWidget{
    Q_OBJECT
public :
    game(int height,int width,QString *name,QHostAddress *,int c,QWidget *parent=0);
    void mousePressEvent( QMouseEvent* ev );
public slots:
    void reciveData();
    void sendData(const QPoint p,int);
private:
    QTcpSocket *mysocket;
    //QMediaPlayer *myplayer;
    QHBoxLayout * qhb;
    QString *mymap;
    QColor * mycolor;
protected:
    void paintEvent(QPaintEvent*);
signals:
    void mousePressed( const QPoint& ,int);


};
#endif //AGAR_GAMEPAGE_H
