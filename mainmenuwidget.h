#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <accounts.h>
#include <game1.h>
#include <QtWidgets>
#include <QTimer>
#include <QObject>
#include <clickablelabel.h>

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(Accounts *curr, QWidget *parent = nullptr);
    Accounts * current_user;
    QLabel *log;
    QLabel *Welcome;
    QGridLayout * grid;
    QVBoxLayout * vbox;
    QGridLayout * gameGrid;
    QLabel *birthday;
    QLabel *img;
    QTimer *timer;
    QSpacerItem *bigSpacer;
    QPushButton *Logout;
    ClickableLabel *Game1Label;
private slots:
    void Blink();
    void PlayGame1();
signals:

};

#endif // MAINMENU_H
