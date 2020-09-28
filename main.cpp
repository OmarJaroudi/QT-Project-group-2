#include "welcomewidget.h"  //this comment was added by merging branch Add-Game1 with master branch
int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    WelcomeWidget * scene = new WelcomeWidget();
    scene->setMinimumSize(300,300);
    scene->show();
    return app.exec();

}
