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
    QLabel *welcome;
    QGridLayout * grid;
    QVBoxLayout * vbox;
    QGridLayout * game_grid;
    QLabel *birthday;
    QLabel *img;
    QTimer *timer;
    QSpacerItem *bigSpacer;
    QPushButton *logout;
    ClickableLabel *game_1_label;
private slots:
    void Blink();
    void PlayGame1();
    void LogOut();
signals:

};

#endif // MAINMENU_H
