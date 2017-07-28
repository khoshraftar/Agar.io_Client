//
// Created by hosseinkh on 7/18/17.
//

#include "AI.h"
#include <iostream>
#include <sstream>
QColor ntoc(int n);
AImode::AImode(int height, int width, QString *name,QHostAddress *IP,int c,QWidget *parent) {
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
    connect(mysocket,SIGNAL(readyRead()),this,SLOT(sendData()));
    setLayout(qhb);
    setStyleSheet("background-color: white");
    show();
}
void AImode::reciveData() {
    *mymap=mysocket->readAll();
    std::stringstream mystream(mymap->toStdString());
    update();
}
void AImode::paintEvent(QPaintEvent *) {
    std::stringstream mystream(mymap->toStdString());
    // me //
    QPainter painter(this);
    int type=-1;
    if(mymap->toStdString()=="Game Over Noob")
    {
        painter.drawText(320,320,"Game Over Noob");
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
            AiFoods a;
            a.x=x;
            a.y=y;
            ai.foods.push_back(a);
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
            Aiopponents a;
            a.x=x;
            a.y=y;
            a.r=r;
            ai.opps.push_back(a);
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
            AiMasses a;
            a.x=x;
            a.y=y;
            ai.masses.push_back(a);
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
    if(f)
    {
        ai.opps.clear();
        ai.foods.clear();
        ai.masses.clear();
    }
}
point Ai::advance() {
    for(int i=0;i<opps.size();i++) {
        if (opps[i].r < 35) {
            std::cout<<"eatable found"<<std::endl;
            point a;
            a.x = opps[i].x;
            a.y = opps[i].y;
            opps.clear();
            foods.clear();
            masses.clear();
            return a;
        }
        if (opps[i].r > 45) {
            point a;
            a.x = -1 * (opps[i].x - 320) + 320;
            a.y = -1 * (opps[i].y - 320) + 320;
            opps.clear();
            foods.clear();
            masses.clear();
            return a;
        }
    }
    if(masses.size()>0)
    {
        point a;
        a.x=masses[0].x;
        a.y=masses[0].y;
        return a;
    }
    srand(time(0));
    int tmpx=rand()%640;
    int tmpy=rand()%640;
    point a;
    a.x=tmpx;
    a.y=tmpy;
    opps.clear();
    foods.clear();
    masses.clear();
    return a;
}
void AImode::sendData() {
    if(f)
    {
        f--;
        return;
    }
    else{f=15;}
    point p=ai.advance();
    std::string sx=std::to_string(p.x);
    std::string sy=std::to_string(p.y);
    QString q = QString::fromLocal8Bit((sx+' '+sy+' '+std::to_string(1)).c_str());
    QByteArray data =&q.toStdString()[0];
    mysocket->write(data);
}