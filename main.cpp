#include "welcomewidget.h"  //this comment was added by merging branch Add-Game1 with master branch
int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    WelcomeWidget * scene = new WelcomeWidget();//initialize first widget displayed
    scene->setMinimumSize(300,300);//set the widgetbsize
    scene->show();
    return app.exec();

}
