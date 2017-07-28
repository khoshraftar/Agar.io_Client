#include <QApplication>
#include "loginpage.h"
int main(int argc,char* argv[]) {
    QApplication *app=new QApplication(argc,argv);
    login a(200,320);
    a.show();
    return app->exec();
}