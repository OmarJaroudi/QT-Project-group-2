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
    QMediaPlayer *smash_sound;
    vector<vector<int>> LoadGrid();

public slots: void ShootVirus();
    void UpdateTime();
    void SpawnVirus();
    void GameOver();


};

#endif // GAME1GRID_H
