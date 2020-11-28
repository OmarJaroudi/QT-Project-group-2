#ifndef GAME1GRID_H
#define GAME1GRID_H
#pragma once
#include <QGraphicsScene>
#include "clickablelabel.h"
#include "virusobject.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QFile>
#include <QPushButton>
#include <QGridLayout>
#include <QTextStream>
#include <QMediaPlayer>
#include <QMediaPlaylist>
using namespace std;
/**
 * @brief The Game1Grid class.
 *
 * Inherits from QGraphicsScene. Is instantiated when user wants to play game 1\n
 *
 * How to play:\n
 * Each virus has a weight (green = 3, yellow = 5,blue = 7)\n
 * Viruses will spawn on screen, and player has to click on them with the mouse\n
 * Clicking aka smashing a virus earns corresponding points\n
 * If player misses 3 viruses, they lose\n
 * Player wins when they reach the final score,\n
 * Player can pause the game by clicking the pause button in top left corner\n
 * A timer, and number of remaining chances is displayed in top right corner.\n
 * When game ends (win or lose), player is prompted to press any button on keyboard, and will be taken back to game1 menu\n
 */
class Game1Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Grid();
    int elapsed_time;
    int current_score;
    int winning_score;
    int current_virus;
    double rolling_speed;
    int current_count;
    bool paused_game;
    bool game_ended;
    bool save_score;
    vector <vector<int>> virus_loc;
    QLabel *timer_info;
    QLabel *score_info;
    QTimer *timer;
    QTimer *spawn_timer;
    QTimer *game_over_timer;
    QLabel *smashed_virus;
    QLabel *pause_button;
    QLabel *chance1;
    QLabel *chance2;
    QLabel *chance3;
    QMediaPlayer *smash_sound;
    VirusObject * new_virus;
    QWidget *pause_menu;
    /**
     * @brief LoadGrid: loads virus combination to be played with from predesigntaed text file
     *
     * Text file is organized line by line with each line having: Virus color - X location- Y location\n
     * First line contains the final score to be reached to win the game.\n
     * Final score is stored in class variable winning_score\n
     * grid of viruses and their locations is stored in class variable virus_loc\n
     * If the viruses included in text file do not mathematically lead to the winning score entered in line 1\n
     * The fucntion wwill discard the text file and generate its own grid with a default winning score of 150\n
     * This is composed of 10 yellow, 10 green, and 10 blue viruses, with randomized order and positions
     *
     * @return vector of vectors, each having [color,x-coord,y-coord]
     */
    vector<vector<int>> LoadGrid();

    /**
     * @brief keyPressEvent: override to go back to game1 menu if game has ended
     *
     * emit gameOver() signal
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    /**
     * @brief ShootVirus. Slot executes if player clicks on virus when it is visible on screen\n
     *
     * If the game is paused, return\n
     * Else:\n
     * Find source of the signal clicked() that was emitted.\n
     * Add the source's score to the total player's score\n
     * Update score label on screen\n
     * Replace clicked virus with smashed virus icon\n
     * Play smashed sound\n
     * For every 5th clicked virus, increment the spawn speed by 1.25
     */
    void ShootVirus();

    /**
     * @brief update the timer label on the screen
     *
     * This slot is connected to a signal that is emitted every 1000 msec.
     */
    void UpdateTime();
    /**
     * @brief Function to spawn a new virus on the screen
     *
     * Instantiate new object of type VirusObject
     * If player hasn't missed any viruses before,
     * Color of virus is from virus_loc[current_virus]
     * Else, missed virus will be stored in VirusObject:missed_shots\n
     * In that case, virus color will be poped from missed_shots (to preserve the posibility of reaching the final score)
     * And location is randomized
     * The clicked signal of the newly created virus object is connected to slot ShootVirus
     */
    void SpawnVirus();

    /**
     * @brief GameOver. Slot connected to a 10msec timer. Aka executes every 10msec
     *
     * Checks if player ahs missed 3 shots, or reached the final winning score.\n
     * Stops all timers and prompts user to press any button to exit Game1Grid
     *
     */
    void GameOver();
    /**
     * @brief Slot connected to clicked() signal of pause_button
     *
     * Stops all QTimer objects, which in turns pauses all possible interrupts\n
     * Displays small widget, from which the player can click "Resume" to resume play, or "Quit" to call emit gameOver() signal
     */
    void ClickPause();
    /**
     * @brief Slot connected to "Resume" button visible from pause menu
     *
     * Restarts all timers
     */
    void ClickContinue();
    /**
     * @brief QuitGame
     *Slot connected to "Quit" button visible from pause menu
     * emits gameOver() signal
     */
    void QuitGame();
signals:
    /**
     * @brief signal connected to GameEnded slot in Game1
     */
    void gameOver();
};

#endif // GAME1GRID_H
