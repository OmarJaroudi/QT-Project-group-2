#include "game2grid.h"

Game2Grid::Game2Grid()
{
    Cells = new vector<ReversiSlot*>();
    setBackgroundBrush(QBrush(QColor::fromRgb(4,140,4),Qt::SolidPattern));
    this->setSceneRect(QRectF(0,0,400,450));
    int r0 = 0;
    for (int i=0;i<8;i++)
    {
        int c0 = 50;

        for (int j=0;j<8;j++){
            ReversiSlot *tempSlot = new ReversiSlot(i,j);
            if ((i==3 && j==3)|| (i==4 && j==4))
                tempSlot->PlaceDisc(ReversiSlot::WHITE);
            else if ((i==3 && j==4) || (i==4 && j==3))
                tempSlot->PlaceDisc(ReversiSlot::BLACK);

            Cells->push_back(tempSlot);
            QObject::connect(Cells->at(i*8+j),SIGNAL(clicked()),this,SLOT(PlayTurn()));
            Cells->at(i*8+j)->move(r0,c0);
            this->addWidget(Cells->at(i*8+j));
            c0+=50;
        }
        r0+=50;
    }

    Game2Grid::turn = ReversiSlot::BLACK;

}
ReversiSlot::COLOR Game2Grid::turn = ReversiSlot::BLACK;
void Game2Grid::PlayTurn(){
    ReversiSlot * source = static_cast<ReversiSlot*>(this->sender());
    if(!source->DiscIsPlaced()){
            source->PlaceDisc(turn);
            if (turn==ReversiSlot::BLACK)
                turn = ReversiSlot::WHITE;
            else turn = ReversiSlot::BLACK;

    }
}
