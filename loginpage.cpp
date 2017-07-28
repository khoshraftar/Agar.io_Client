#include "loginpage.h"
login::login(int height,int width,QWidget * parent) :QWidget(parent){
    QRect rec = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(rec.width() / 2 - width / 2, rec.height() / 2 - height / 2, width, height);
    Q1=new QHBoxLayout;
    Q2=new QHBoxLayout;
    Q3=new QHBoxLayout;
    Q4=new QHBoxLayout;
    l1=new QLabel("Username:");
    le1=new QLineEdit("How Are You");
    l2=new QLabel("server IP:");
    le2=new QLineEdit("127.0.0.1");
    l3=new QLabel("CPU Player");
    l4=new QLabel("Specter Mode");
    CH=new QCheckBox;
    CH2=new QCheckBox;
    menu2=new QComboBox;
    menu2->addItem("Player 1");
    menu2->addItem("Player 2");
    menu2->addItem("Player 3");
    menu2->addItem("Player 4");
    menu2->addItem("Player 5");
    menu2->addItem("Player 6");
    menu2->addItem("Player 7");
    menu2->addItem("Player 8");
    menu2->addItem("Player 9");
    menu=new QComboBox;
    menu->addItem("black");
    menu->addItem("white");
    menu->addItem("dark gray");
    menu->addItem("light gray");
    menu->addItem("gray");
    menu->addItem("red");
    menu->addItem("green");
    menu->addItem("blue");
    menu->addItem("cyan");
    menu->addItem("magenta");
    menu->addItem("yellow");
    menu->addItem("dark red");
    menu->addItem("dark green");
    menu->addItem("dark blue");
    menu->addItem("dark cyan");
    menu->addItem("dark magenta");
    menu->addItem("dark yellow");
    Q1->addWidget(l1);
    Q1->addWidget(le1);
    Q2->addWidget(l2);
    Q2->addWidget(le2);
    Q3->addWidget(l3);
    Q3->addWidget(CH);
    Q3->addWidget(menu);
    Q4->addWidget(l4);
    Q4->addWidget(CH2);
    Q4->addWidget(menu2);
    btn=new QPushButton("Login");
    V1=new QVBoxLayout;
    V1->addLayout(Q1);
    V1->addLayout(Q2);
    V1->addLayout(Q3);
    V1->addLayout(Q4);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox -> addButton(btn, QDialogButtonBox::RejectRole);
    V1->addWidget(buttonBox);
    setLayout(V1);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(request_login()));
    show();
}
void login::request_login() {
  this->hide();
    if(!CH->isChecked() && !CH2->isChecked())
    {
        QString *a = new QString(le1->text());
        QHostAddress *b = new QHostAddress(le2->text());
        game *mygame = new game(640, 640, a, b, menu->currentIndex());
    }
    if(!CH->isChecked() && CH2->isChecked())
    {
        QString *a = new QString(le1->text());
        QHostAddress *b = new QHostAddress(le2->text());
        Smode *mySmode = new Smode(640, 640, a, b, menu->currentIndex(),menu2->currentIndex());
    }
    if(CH->isChecked() && !CH2->isChecked())
    {
        QString *a = new QString(le1->text());
        QHostAddress *b = new QHostAddress(le2->text());
        AImode *myAi = new AImode(640, 640, a, b, menu->currentIndex());
    }
}
