#ifndef GAME1GRID_H
#define GAME1GRID_H
#include <QGraphicsScene>
#include "clickablelabel.h"
#include "virusobject.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFile>
#include <QPushButton>
#include <QGridLayout>
#include <QVector> // for 2D vector
#include <QThread>
using namespace std;
class Game1Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Grid();
    //Game1 * game_menu;
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
    vector<vector<int>> LoadGrid();
    VirusObject * new_virus;
    QWidget *pause_menu;
    void keyPressEvent(QKeyEvent *event) override;

public slots: void ShootVirus();
    void UpdateTime();
    void SpawnVirus();
    void GameOver();
    void ClickPause();
    void ClickContinue();
    void QuitGame();
signals:void gameOver();
};

#endif // GAME1GRID_H
