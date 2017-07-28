//
// Created by hosseinkh on 7/13/17.
//
//
// Created by hosseinkh on 6/29/17.
//
#include "Spectator.h"
#include <iostream>
#include <sstream>
#include <iostream>
QColor ntoc(int n);
Smode::Smode(int height, int width, QString *name,QHostAddress *IP,int c, int p,QWidget *parent) {
    QRect rec = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(rec.width() / 2 - width / 2, rec.height() / 2 - height / 2, width, height);
    mymap=new QString("");
    mysocket=new QTcpSocket;
    mysocket->connectToHost(*IP,4444);
    std::string stmp=std::to_string((p+1)*100);
    QString tmp=QString::fromStdString(stmp);
    QByteArray qba=&tmp.toStdString()[0];
    mysocket->write(qba);
    mycolor=new QColor;
    *mycolor=ntoc(c);
    qhb=new QHBoxLayout;
    connect(mysocket,SIGNAL(readyRead()),this,SLOT(reciveData()));
    setLayout(qhb);
    setStyleSheet("background-color: white");
    show();
}
void Smode::reciveData() {
    *mymap=mysocket->readAll();
    std::stringstream mystream(mymap->toStdString());
    update();
}
void Smode::paintEvent(QPaintEvent *) {
    std::stringstream mystream(mymap->toStdString());
    // me //
    QPainter painter(this);
    int type=-1;
    if(mymap->toStdString()=="Game Over Noob")
    {
        painter.drawText(320,320,"your player was noob");
        return ;
    }
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