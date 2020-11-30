#ifndef GAME2_H
#define GAME2_H
#pragma once
#include <QWidget>
#include "mainmenuwidget.h"
#include "game2grid.h"
#include "accounts.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
/**
 * @brief The Game1 class instantiated when user clicks on game2 label from main menu
 */
class Game2 : public QWidget
{
    Game2Grid * grid;
    Accounts *player;
    QPushButton *play_button;
    QVBoxLayout *v_layout;
    QHBoxLayout *layout;
    QPushButton *back_button;
    QGraphicsView *view;
    QLineEdit * player2Name;
    QLabel *error;
    QRadioButton * pick_white;
    QRadioButton * pick_black;
    QSpacerItem *spacer;
    Q_OBJECT
public:
    /**
     * @brief keyPressEvent: overloaded so that if user presses f1, game 2 will start
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief Game2 constructor, needs to know the account of the user that is going to play, for score keeping purposes later on
     * @param acc
     * @param parent
     */
    explicit Game2(Accounts *acc,QWidget *parent = nullptr);
public slots:
    /**
     * @brief PressBack: slot executes if user presses back_button, takes them back to main menu widget
     *
     * closes current Game2 widget, and instantiates new pointer of type MainMenu
     */
    void PressBack();
    /**
     * @brief StartGame: slot executes if user presses on play_button, instantiates Game2Grid.\n
     *
     * Same function accomplished by pressing f1 key
     */
    void StartGame();
    /**
     * @brief GameEnded: slot executes when Game2Grid emits gameOver signal\n
     *
     * If the user has completed a game and is signed in (not guest), this function will save the score
     * by calling the history class
     */
    void GameEnded();
    /**
     * @brief GameEnded: slot executes when Game2Grid emits gameOver signal\n
     *
     * This function deletes the game window and returns the user to the home screen
     */
    void ScoreUpdated();
    /**
     * @brief GameEnded: slot executes when Game2Grid emits updateScore signal\n
     *
     * This fucntion calls the UpdateHistory(int score, int game) to potentially update the user's high score
     */
signals:

};

#endif // GAME2_H
