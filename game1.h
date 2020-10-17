#ifndef GAME1_H
#define GAME1_H

#include <QWidget>
#include <QtWidgets>
#include "accounts.h"
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>
#include "mainmenuwidget.h"

class Game1 : public QWidget
{
    Accounts *player;
    QPushButton *play_button;
    QVBoxLayout *difficulty_layout;
    QVBoxLayout *layout;
    QPushButton *easy;
    QPushButton *medium;
    QPushButton *hard;
    QPushButton *back_button;
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    explicit Game1(Accounts *acc,QWidget *parent = nullptr);
public slots: void ChooseDifficulty();
    void PressBack();
signals:

};

#endif // GAME1_H