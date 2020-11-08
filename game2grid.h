#ifndef GAME2GRID_H
#define GAME2GRID_H

#include <QObject>
#include <QGraphicsScene>
#include "reversislot.h"
#include <vector>
#include <QDebug>
using namespace std;

class Game2Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    vector <ReversiSlot*> * Cells;
    Game2Grid();
    static ReversiSlot::COLOR turn;
public slots: void PlayTurn();
signals:void gameOver();

};

#endif // GAME2GRID_H
