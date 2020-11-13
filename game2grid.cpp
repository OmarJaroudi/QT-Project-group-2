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

    vector<ReversiSlot*>* test=ValidMove();
    for(int i=0;i<(int)test->size();i++)
    {
        qDebug()<<test->at(i)->x*8+test->at(i)->y<<test->at(i)->x<<test->at(i)->y;
    }
}

vector<ReversiSlot*>* Game2Grid::ValidMove()
{
    vector<ReversiSlot*> *result= new vector<ReversiSlot*>();

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(!Cells->at(8*i+j)->DiscIsPlaced())
            {
                //cell we're looking at: 8i+j
                if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }

                if(8*i-8+j>=0 && 8*i-8+j<63)
                {
                    if(Cells->at(8*i-8+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-8+j)->y==Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-8+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-8+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-16+m+j>=0 && 8*i-16+m+j<64)
                                {
                                    if(Cells->at(8*i-16+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-16+j+m)->y==Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-16+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-16+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-8;
                                }
                            }
                        }
                    }
                }
                if(8*i-7+j>=0 && 8*i-7+j<63)
                {
                    if(Cells->at(8*i-7+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-7+j)->y>Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-7+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-7+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-14+m+j>=0 && 8*i-14+m+j<64)
                                {
                                    if(Cells->at(8*i-14+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-14+j+m)->y>Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-14+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-14+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-7;
                                }
                            }
                        }
                    }
                }

                if(8*i+1+j>=0 && 8*i+1+j<63)
                {
                    if(Cells->at(8*i+1+j)->x==Cells->at(8*i+j)->x && Cells->at(8*i+1+j)->y>Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i+1+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i+1+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i+2+m+j>=0 && 8*i+2+m+j<64)
                                {
                                    if(Cells->at(8*i+2+j+m)->x==Cells->at(8*i+j)->x && Cells->at(8*i+2+j+m)->y>Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j+2+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j+2+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=1;
                                }
                            }
                        }
                    }
                }

                if(8*i+9+j>=0 && 8*i+9+j<63)
                {
                    if(Cells->at(8*i+9+j)->x>Cells->at(8*i+j)->x && Cells->at(8*i+9+j)->y>Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i+9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i+9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i+18+m+j>=0 && 8*i+18+m+j<64)
                                {
                                    if(Cells->at(8*i+18+j+m)->x>Cells->at(8*i+j)->x && Cells->at(8*i+18+j+m)->y>Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j+18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j+18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=9;
                                }
                            }
                        }
                    }
                }

                if(8*i+8+j>=0 && 8*i+8+j<63)
                {
                    if(Cells->at(8*i+8+j)->x>Cells->at(8*i+j)->x && Cells->at(8*i+8+j)->y==Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i+8+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i+8+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i+16+m+j>=0 && 8*i+16+m+j<64)
                                {
                                    if(Cells->at(8*i+16+j+m)->x>Cells->at(8*i+j)->x && Cells->at(8*i+16+j+m)->y==Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j+16+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j+16+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=8;
                                }
                            }
                        }
                    }
                }

                if(8*i+7+j>=0 && 8*i+7+j<63)
                {
                    if(Cells->at(8*i+7+j)->x>Cells->at(8*i+j)->x && Cells->at(8*i+7+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i+7+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i+7+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i+14+m+j>=0 && 8*i+14+m+j<64)
                                {
                                    if(Cells->at(8*i+14+j+m)->x>Cells->at(8*i+j)->x && Cells->at(8*i+14+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j+14+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j+14+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=7;
                                }
                            }
                        }
                    }
                }

                if(8*i-1+j>=0 && 8*i-1+j<63)
                {
                    if(Cells->at(8*i-1+j)->x==Cells->at(8*i+j)->x && Cells->at(8*i-1+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-1+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-1+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-2+m+j>=0 && 8*i-2+m+j<64)
                                {
                                    if(Cells->at(8*i-2+j+m)->x==Cells->at(8*i+j)->x && Cells->at(8*i-2+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-2+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-2+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-1;
                                }
                            }
                        }
                    }
                }

            }
                /*else if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }
                else if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }
                else if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }
                else if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }
                else if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }
                else if(8*i-9+j>=0 && 8*i-9+j<63)
                {
                    if(Cells->at(8*i-9+j)->x<Cells->at(8*i+j)->x && Cells->at(8*i-9+j)->y<Cells->at(8*i+j)->y)
                    {
                        if(Cells->at(8*i-9+j)->DiscIsPlaced())
                        {
                            if(Cells->at(8*i-9+j)->current_color!=turn)
                            {
                                int m=0;
                                while(8*i-18+m+j>=0 && 8*i-18+m+j<64)
                                {
                                    if(Cells->at(8*i-18+j+m)->x<Cells->at(8*i+j)->x && Cells->at(8*i-18+j+m)->y<Cells->at(8*i+j)->y)
                                    {
                                        if(Cells->at(8*i+j-18+m)->DiscIsPlaced())
                                        {
                                            if(Cells->at(8*i+j-18+m)->current_color==turn)
                                            {
                                                result->push_back(Cells->at(8*i+j));
                                                break;
                                            }
                                        }
                                        else break;
                                    }
                                    m+=-9;
                                }
                            }
                        }
                    }
                }*/

            }




        }

    return result;
}
