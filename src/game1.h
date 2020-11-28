#ifndef GAME1_H
#define GAME1_H
#include <QWidget>
#include <QDesktopWidget>
#include <QGraphicsView>
#include "accounts.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "mainmenuwidget.h"
#include "game1grid.h"

/**
 * @brief The Game1 class instantiated when user clicks on game1 from main menu
 */
class Game1 : public QWidget
{
    Game1Grid * grid;
    Accounts *player;
    QPushButton *play_button;
    QVBoxLayout *difficulty_layout;
    QVBoxLayout *layout;
    QPushButton *back_button;
    QGraphicsView *view;

    Q_OBJECT
public:
    /**
     * @brief keyPressEvent: overloaded so that if user presses f1, game 1 will start
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief Game1 constructor, needs to know the account of the user that is going to play, for score keeping purposes later on
     * @param acc
     * @param parent
     */
    explicit Game1(Accounts *acc,QWidget *parent = nullptr);
public slots:
    /**
     * @brief PressBack: slot executes if user presses back_button, takes them back to main menu widget
     */
    void PressBack();
    /**
     * @brief StartGame: slot executes if user presses on play_button, instantiates Game1Grid.\n
     *
     * Same function accomplished by pressing f1 key
     */
    void StartGame();

    /**
     * @brief GameEnded: slot executes when Game1Grid emits gameOver signal\n
     *
     * If the user has completed a game and is signed in (not guest), this function will save the score
     * by calling the history class
     */
    void GameEnded();
signals:

};

#endif // GAME1_H
