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
using namespace std;
class Game1Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    Game1Grid();
    int elapsed_time;
    int current_score;
    int winning_score;
    int current_virus;
    double rolling_speed;
    int current_count;
    vector <vector<int>> virus_loc;
    QLabel *timer_info;
    QLabel *score_info;
    QTimer *timer;
    QTimer *spawn_timer;
    QTimer *game_over_timer;
    QLabel *blue_virus;
    QLabel *yellow_virus;
    QLabel *green_virus;
    QLabel *smashed_virus;
    QLabel *pause_button;
    QMediaPlayer *smash_sound;
    vector<vector<int>> LoadGrid();
    VirusObject * new_virus;
    QWidget *pause_menu;

public slots: void ShootVirus();
    void UpdateTime();
    void SpawnVirus();
    void GameOver();
    void ClickPause();
    void ClickContinue();

signals:void gameOver();
};

#endif // GAME1GRID_H
