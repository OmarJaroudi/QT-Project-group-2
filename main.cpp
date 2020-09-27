#include "welcomewidget.h"
int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    WelcomeWidget * scene = new WelcomeWidget();
    scene->setMinimumSize(300,300);
    scene->show();
    return app.exec();

}
