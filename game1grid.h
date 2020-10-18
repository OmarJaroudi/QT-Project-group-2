#ifndef GAME1GRID_H
#define GAME1GRID_H
#include <QGraphicsScene>
#include "clickablelabel.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
class game1grid : public QGraphicsScene
{
    Q_OBJECT
public:
    game1grid();
    QLabel *blue_virus;
    QLabel *yellow_virus;
    QLabel *green_virus;
public slots: void ShootVirus();

};

#endif // GAME1GRID_H
