#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include <QWidget>
#include "accounts.h"
#include "game1.h"
#include "game2.h"
#include <QtWidgets>
#include <QTimer>
#include <QObject>
#include <clickablelabel.h>
#include <historywidget.h>

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
    QPushButton *history;
    ClickableLabel *game_1_label;
    ClickableLabel *game_2_label;

private slots:
    void Blink();
    void PlayGame1();
    void PlayGame2();
    void LogOut();
    void history_clicked();
signals:

};

#endif // MAINMENU_H
