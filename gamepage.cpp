//
// Created by hosseinkh on 6/29/17.
//
#include "gamepage.h"
#include <iostream>
#include <sstream>
#include <iostream>
QColor ntoc(int n);
game::game(int height, int width, QString *name,QHostAddress *IP,int c, QWidget *parent) {
    QRect rec = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(rec.width() / 2 - width / 2, rec.height() / 2 - height / 2, width, height);
    mymap=new QString("");
    mysocket=new QTcpSocket;
    mysocket->connectToHost(*IP,4444);
    std::string stmp=std::to_string(c);
    QString tmp=QString::fromStdString(stmp);
    QByteArray qba=&tmp.toStdString()[0];
    mysocket->write(qba);
    mycolor=new QColor;
    *mycolor=ntoc(c);
    qhb=new QHBoxLayout;
    connect(mysocket,SIGNAL(readyRead()),this,SLOT(reciveData()));
    connect(this,SIGNAL(mousePressed(QPoint,int)),this,SLOT(sendData(QPoint,int)));
    setLayout(qhb);
    setStyleSheet("background-color: white");
    show();
}
void game::reciveData() {
    *mymap=mysocket->readAll();
    update();
}
QColor ntoc(int n)
{
    if(n==0)
        return Qt::black;
    if(n==1)
        return Qt::white;
    if(n==2)
        return Qt::darkGray;
    if(n==3)
        return Qt::gray;
    if(n==4)
        return Qt::lightGray;
    if(n==5)
        return Qt::red;
    if(n==6)
        return Qt::green;
    if(n==7)
        return Qt::blue;
    if(n==8)
        return Qt::cyan;
    if(n==9)
        return Qt::magenta;
    if(n==10)
        return Qt::yellow;
    if(n==11)
        return Qt::darkRed;
    if(n==12)
        return Qt::darkGreen;
    if(n==13)
        return Qt::darkBlue;
    if(n==14)
        return Qt::darkCyan;
    if(n==15)
        return Qt::darkMagenta;
    if(n==16)
        return Qt::darkYellow;
}
void game::paintEvent(QPaintEvent *) {
    std::stringstream mystream(mymap->toStdString());
    // me //
    QPainter painter(this);
    if(mymap->toStdString()=="Game Over Noob")
    {
        painter.drawText(320,320,"Game Over Noob");
        return ;
    }
    int type=-1;
    while(!mystream.eof())
    {
        //  me  //
        if(type==-1)
        {
            int myr,x,y;
            mystream>>myr;
            if(myr==-99999)
            {
                type++;
                continue;
            }
            mystream>>x>>y;
            //painter.setPen(*mycolor);
            painter.setBrush(*mycolor);
            painter.drawEllipse(x-myr/2,y-myr/2,myr,myr);
        }
        // foods //
        if(type==0)
        {
            int x,y,r,color;
            mystream>>x;
            if(x==-99999)
            {
                type++;
                continue;
            }
            mystream>>y>>r>>color;
            painter.setPen(ntoc(color));
            painter.setBrush(ntoc(color));
            painter.drawEllipse(x-r/2,y-r/2,r,3*r/4);
        }
        // oponents //
        if(type==1)
        {
            int x,y,r,color;
            mystream>>x;
            if(x==-99999)
            {
                type++;
                continue;
            }
            mystream>>y>>r>>color;
            //painter.setPen(ntoc(color));
            painter.setBrush(ntoc(color));
            painter.drawEllipse(x-r/2,y-r/2,r,r);
        }
        // mass //
        if(type==2)
        {
            int x,y,r,color;
            mystream>>x;
            if(x==-99999)
            {
                type++;
                continue;
            }
            mystream>>y>>r>>color;
            QPen pen=painter.pen();
            pen.setWidth(4);
            pen.setColor(ntoc(0));
            painter.setPen(pen);
            painter.setBrush(ntoc(color));
            painter.drawEllipse(x-r/2,y-r/2,r,r);
        }
        painter.setPen(1);
        // virus //
        if(type==3)
        {
            int x,y,r;
            mystream>>x;
            if(x==-99999)
                return;
            mystream>>y>>r;
            QPen pen=painter.pen();
            pen.setColor(ntoc(0));
            painter.setPen(pen);
            QBrush brushs(Qt::darkGreen);
            brushs.setStyle(Qt::Dense2Pattern);
            painter.setBrush(brushs);
            if(r>100)
                break;
            painter.drawEllipse(x-r/2,y-r/2,r,r);

        }
    }
}
void game::sendData(const QPoint p,int type) {
    std::string sx=std::to_string(p.x());
    std::string sy=std::to_string(p.y());
    QString q = QString::fromLocal8Bit((sx+' '+sy+' '+std::to_string(type)).c_str());
    QByteArray data =&q.toStdString()[0];
    mysocket->write(data);
}
void game::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    int type=3;
    if(ev->buttons() == Qt::RightButton)
        type=2;
    if(ev->buttons() == Qt::LeftButton)
        type=1;
    emit mousePressed( p,type );
}