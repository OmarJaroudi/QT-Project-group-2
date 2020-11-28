#include "welcomewidget.h"  //this comment was added by merging branch Add-Game1 with master branch
#include <QApplication>
int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    WelcomeWidget * scene = new WelcomeWidget();//initialize first widget displayed
    scene->show();
    return app.exec();

}
