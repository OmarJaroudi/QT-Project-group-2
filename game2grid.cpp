#include "game2grid.h"

Game2Grid::Game2Grid()
{
    setBackgroundBrush(QBrush(QColor::fromRgb(4,140,4),Qt::SolidPattern));
    this->setSceneRect(QRectF(0,0,400,450));
    int r0 = 0;
    for (int i=0;i<8;i++)
    {
        int c0 = 50;

        for (int j=0;j<8;j++){
            ReversiSlot *slot = new ReversiSlot(i,j);
            QObject::connect(slot,SIGNAL(clicked()),this,SLOT(ShowDisc()));
            this->AvailableSlots.push_back(slot);
            slot->move(r0,c0);
            this->addWidget(slot);
            c0+=50;
        }
        r0+=50;
    }

}
void Game2Grid::ShowDisc(){

    static_cast<ReversiSlot*>(this->sender())->setIconSize(QSize(100,100));
    QIcon checker(QPixmap(":/thumbnails/white_checker.png").scaled(45,45));
    static_cast<ReversiSlot*>(this->sender())->setIcon(checker);
}
