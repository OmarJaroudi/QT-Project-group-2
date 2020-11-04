#ifndef GAME2_H
#define GAME2_H
#pragma once
#include <QWidget>
#include <QtWidgets>
#include "mainmenuwidget.h"

#include "accounts.h"
class Game2 : public QWidget
{
    //Game1Grid * grid;
    Accounts *player;
    QPushButton *play_button;
    QVBoxLayout *difficulty_layout;
    QHBoxLayout *layout;
    QPushButton *back_button;
    QGraphicsView *view;

    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    explicit Game2(Accounts *acc,QWidget *parent = nullptr);
public slots:
    void PressBack();
    void StartGame();
    void GameEnded();
signals:

};

#endif // GAME2_H
