#ifndef GAME1_H
#define GAME1_H

#include <QWidget>
#include <QtWidgets>
#include "accounts.h"
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>

class Game1 : public QWidget
{
    Accounts *player;
    QPushButton *playButton;
    QVBoxLayout *layout;
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    explicit Game1(Accounts *acc,QWidget *parent = nullptr);

signals:

};

#endif // GAME1_H
