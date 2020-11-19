#ifndef GAME2GRID_H
#define GAME2GRID_H

#include <QObject>
#include <QGraphicsScene>
#include "reversislot.h"
#include <vector>
#include <QDebug>
#include <QLabel>
using namespace std;

class Game2Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    vector <ReversiSlot*> * Cells;
    Game2Grid();
    QPushButton *back_button;
    static ReversiSlot::COLOR turn;
    vector<ReversiSlot*>* ValidMove();
    vector<vector<int>> ValidMove2(int x, int y);
    vector<vector<int>> ExplorePath(int x0,int y0,int x_direction,int y_direction);
    vector<vector<int>> AllValidMoves();
    static vector<vector<int>> all_valid_moves;
    QLabel * turn_label;
    void DisplayHints();
    QString save_score;
public slots: void PlayTurn();
    void PressBack();
signals:void gameOver();

};

#endif // GAME2GRID_H
