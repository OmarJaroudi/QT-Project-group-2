#ifndef GAME2GRID_H
#define GAME2GRID_H

#include <QObject>
#include <QGraphicsScene>
#include "reversislot.h"
#include <vector>
#include <QDebug>
#include <QLabel>
using namespace std;
/**
 * @brief The Game2Grid class: Where user can actually play Game2. Accessed after user presses f1 key or play_button from Game2 widget
 *
 */
class Game2Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    vector <ReversiSlot*> * Cells;
    /**
     * @brief Game2Grid: default constructor\n
     *
     * Intializes the gird visual's. Grid is 8x8 ReversiSlots, with 4 set discs in the center\n
     * The 64 slots are saved in a 1d vector as pointers\n
     * Their clicked signal is connected to slot PlayTurn\n
     * Initializes global variable turn to black since game always starts with black's turn
     *
     */
    Game2Grid();
    /**
     * @brief back_button:QPushButton whose signal clicked is connected to Slot PressBack
     */
    QPushButton *back_button;
    /**
     * @brief static variable to keep track of who's turn it is. Starts as black, then typically alternates between enums BLACK and WHITE
     *
     * This variable dictates what color the next disc that is placed on the grid will be
     */
    static ReversiSlot::COLOR turn;
    /**
     * @brief ValidMove: Function checks if a ReversiSlot at position (x,y) can be played as a turn in the game
     *
     * For a move to be valid, it must lead to at least 1 of the opponents discs to be flipped.\n
     * This function checks in all 8 possible path (N,S,E,W,NE,NW,SE,SW) if such a disc exists
     *
     *
     * @return vector of all discs that should be flipped if the move at (x,y) is played. If vector is empty, move is illegal
     */
    vector<vector<int>> ValidMove(int x, int y);
    /**
     * @brief ExplorePath: Explores a path (N,S,E,W,NE,NW,SE,SW) to tell if any discs can be flipped if move (x0,y0) is played
     * @param x0
     * @param y0
     * @param x_direction: {-1,0,1} to indicate in what increment we should move along the rows
     * @param y_direction: {-1,0,1} to indicate in what increments we should move aling the columns
     *
     * starting from x0,y0 proceed in increments of (+x_direction,+y_direction) and check:\n
     * If slot is empty-->empty return vector and return\n
     * If slot has a disc of same color --> return\n
     * If slot has a disc of opposite color --> add (x_slot,y_slot) to return vector\n
     * If end of board is reached without reaching slot of same color first -->emtpy return vector and return\n
     * @return vector of all discs that can be flipped in specified path. if vector is empty,
     * nothing can be said about legality of the move, since other paths have to be checked
     */
    vector<vector<int>> ExplorePath(int x0,int y0,int x_direction,int y_direction);
    /**
     * @brief AllValidMoves: For all cells in grid, check if each cell is a valid move
     *
     * In a doubly nested loop, call ValidMove on each cell in 8x8 grid\n
     * If move is valid, store coordinates in return vector
     * Return 2d vector containing coordinates of all valid moves in grid
     * @return
     */
    vector<vector<int>> AllValidMoves();
    static vector<vector<int>> all_valid_moves;
    QLabel * turn_label;
    QString save_score;
public slots:
    /**
     * @brief PlayTurn: Slot connected to click signal for all ReversiSlots in grid
     *
     * Checks if x and y coords of clicked slot are in all_valid_moves.\n
     * If not, return\n
     * If it exists, call ValidMove(x,y) to decide on what discs must be flipped\n
     * For each disc in returned vector, change color to its opposite color (black to white and vice versa)\n
     * Update static variable turn\n
     * Update all_valid_moves by calling AllValidMoves\n
     * If updated all_valid_moves is empty, the next player cannot make a move\n
     * Reset turn to the player who just played, and call AllValidMoves\n
     * If updated all_valid_moves is again empty, the current player cannot make a move as well, meaning both players can't play\n
     * Game has ended\n
     * If so, compute the number of placed white discs and the black ones\n
     * The player having more discs is the winner
     */
    void PlayTurn();

    /**
     * @brief PressBack:Slot connected to clicked() signal of back_button
     * emits signal gameOver() which is connected to a slot in Game2
     */
    void PressBack();
signals:
    /**
     * @brief signal emitted in PressBack(), aka when user clicks back_button
     */
    void gameOver();

};

#endif // GAME2GRID_H
