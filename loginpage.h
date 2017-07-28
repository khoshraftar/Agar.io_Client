#ifndef PROJ1_LOGINPAGE_H
#define PROJ1_LOGINPAGE_H
#include <QWidget>
#include <QtWidgets>
#include "gamepage.h"
#include "Spectator.h"
#include "AI.h"
class login :public QWidget{
    Q_OBJECT
public:
    login(int,int,QWidget * parent= 0);
private:
    QHBoxLayout *Q1;
    QHBoxLayout *Q2;
    QHBoxLayout *Q3;
    QHBoxLayout *Q4;
    QLabel* l1;
    QLineEdit* le1;
    QLabel* l2;
    QLineEdit *le2;
    QPushButton *btn;
    QVBoxLayout *V1;
    QLabel *l3;
    QCheckBox *CH;
    QComboBox *menu;
    QLabel *l4;
    QCheckBox *CH2;
    QComboBox *menu2;
    //signals:
      // void loginrequested(QString *);
   public slots:
     void request_login();
};
#endif //PROJ1_LOGINPAGE_H
