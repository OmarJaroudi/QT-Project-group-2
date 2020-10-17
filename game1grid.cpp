#include "game1grid.h"

game1grid::game1grid()
{
    this->setSceneRect(0,0,1000,400);
    for (int x=0; x<=1000;x+=100)
        this->addLine(x,0,x,10000, QPen(Qt::black));

    // Now add the horizontal lines, paint them green
    for (int y=0; y<=400; y+=100)
        this->addLine(0,y,1000,y, QPen(Qt::black));
}
