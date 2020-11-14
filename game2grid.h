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
    vector<ReversiSlot*>* ValidMove();
    bool ValidMove2(int x, int y);
    vector<vector<int>> ExplorePath(int x0,int y0,int x_direction,int y_direction);
public slots: void PlayTurn();
signals:void gameOver();

};

#endif // GAME2GRID_H
