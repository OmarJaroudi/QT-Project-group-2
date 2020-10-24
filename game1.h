#ifndef GAME1_H
#define GAME1_H
#include <QWidget>
#include <QtWidgets>
#include "accounts.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "mainmenuwidget.h"
#include "game1grid.h"

class Game1 : public QWidget
{
    Game1Grid * grid;
    Accounts *player;
    QPushButton *play_button;
    QVBoxLayout *difficulty_layout;
    QVBoxLayout *layout;
    QPushButton *back_button;
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    explicit Game1(Accounts *acc,QWidget *parent = nullptr);
public slots:
    void PressBack();
    void StartGame();
    void SaveScore();
signals:

};

#endif // GAME1_H
