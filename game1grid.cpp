#include "game1grid.h"

game1grid::game1grid()
{
    QPen line = (QPen(QColor::fromRgb(42,46,51)));
    line.setWidth(10);
    this->setSceneRect(0,0,1000,400);
    for (int x=0; x<=1000;x+=100)
        this->addLine(x,0,x,10000,line);

    // Now add the horizontal lines, paint them green
    for (int y=0; y<=400; y+=100)
        this->addLine(0,y,1000,y, line);

    setBackgroundBrush(QBrush(QColor::fromRgb(128,0,0),Qt::SolidPattern));
    //setBackgroundBrush(QBrush(QColor::fromRgb(128,0,0),Qt::SolidPattern));
}
