#include "game2grid.h"

vector<vector<int>> Game2Grid::all_valid_moves;

Game2Grid::Game2Grid()
{
    int_save_score=0;
    save_score = "";
    back_button = new QPushButton();
    back_button->setIcon(QIcon(":/thumbnails/back_button.png"));
    back_button->setIconSize(QSize(30, 30));
    back_button->setFixedSize(30,30);
    back_button->move(0,20);
    this->addWidget(back_button);

    turn_label = new QLabel("Black's turn");
    this->addWidget(turn_label);
    turn_label->move(140,20);
    turn_label->setFixedSize(150,40);
    turn_label->setStyleSheet("QLabel {background-color: rgba(0,0,0,0%);font-size:20px;}");
    Cells = new vector<ReversiSlot*>();
    setBackgroundBrush(QBrush(QColor::fromRgb(4,140,4),Qt::SolidPattern));
    this->setSceneRect(QRectF(0,0,400,450));
    int r0 = 50;
    for (int i=0;i<8;i++)
    {
        int c0 = 0;

        for (int j=0;j<8;j++){
            ReversiSlot *tempSlot = new ReversiSlot(i,j);
            if ((i==3 && j==3)|| (i==4 && j==4))
                tempSlot->PlaceDisc(ReversiSlot::WHITE);
            else if ((i==3 && j==4) || (i==4 && j==3))
                tempSlot->PlaceDisc(ReversiSlot::BLACK);

            Cells->push_back(tempSlot);
            QObject::connect(Cells->at(i*8+j),SIGNAL(clicked()),this,SLOT(PlayTurn()));
            Cells->at(i*8+j)->move(c0,r0);
            this->addWidget(Cells->at(i*8+j));
            c0+=50;
        }
        r0+=50;
    }

    Game2Grid::turn = ReversiSlot::BLACK;
    all_valid_moves = this->AllValidMoves();
    QObject::connect(back_button,SIGNAL(clicked()),this,SLOT(PressBack()));

}


ReversiSlot::COLOR Game2Grid::turn = ReversiSlot::BLACK;

void Game2Grid::PlayTurn(){
    ReversiSlot * source = static_cast<ReversiSlot*>(this->sender());
    std::vector<vector<int>>::iterator it2 = std::find(all_valid_moves.begin(), all_valid_moves.end(),
                                                       vector<int>{source->x,source->y});
    if (it2 == all_valid_moves.end())
        return;


    std::vector<ReversiSlot*>::iterator it = std::find(Cells->begin(), Cells->end(), source);
    if (it != Cells->end()){
        int index = std::distance(Cells->begin(), it);
        source = Cells->at(index);
    }

    vector<vector<int>> result = ValidMove(source->x,source->y);
    if (result.size()!=0){
        for (int i=0;i<result.size();i++){
            this->Cells->at(result[i][0]*8+result[i][1])->Flip();
        }
        source->PlaceDisc(turn);
        vector<vector<int>> back_up = AllValidMoves();
        ReversiSlot::COLOR same_color = turn;
        if (turn==ReversiSlot::BLACK)
            turn = ReversiSlot::WHITE;
        else
            turn = ReversiSlot::BLACK;
        all_valid_moves = AllValidMoves();
        if (all_valid_moves.size()==0){
            all_valid_moves = back_up;
            turn = same_color;
        }

        if (all_valid_moves.size()==0){
            int white_count = 0;
            int black_count = 0;
            for (int i=0;i<8;i++){
                for (int j=0;j<8;j++){
                    if (Cells->at(i*8+j)->current_color==ReversiSlot::BLACK)
                        black_count+=1;
                    else
                        white_count+=1;
                }
            }
            if (white_count>black_count){
                turn_label->setText("White wins!");
                turn_label->setStyleSheet("QLabel {background-color: rgba(0,0,0,0%);font-size:20px;color:white;}");
                int_save_score=white_count;
                emit(updateScore());

            }
            else if (white_count<black_count){
                turn_label->setText("Black wins!");
                turn_label->setStyleSheet("QLabel {background-color: rgba(0,0,0,0%);font-size:20px;color:black;}");
                int_save_score=black_count;
                emit(updateScore());
            }
            else
                turn_label->setText("Draw");
            save_score = "white=" + QString::number(white_count) + ",black=" + QString::number(black_count);
            //qDebug()<<int_save_score;
            return;
        }

        if(turn==ReversiSlot::BLACK){
            turn_label->setText("Black's turn");
            turn_label->setStyleSheet("QLabel {background-color: rgba(0,0,0,0%);font-size:20px;color:black;}");
        }
        else {
            turn_label->setText("White's turn");
            turn_label->setStyleSheet("QLabel {background-color: rgba(0,0,0,0%);font-size:20px;color:white;}");
        }
    }

}

vector<vector<int>> Game2Grid::AllValidMoves(){
    vector<vector<int>> all_valid_moves;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (this->Cells->at(i*8+j)->DiscIsPlaced())
                continue;
            vector<vector<int>> temp = ValidMove(i,j);
            if (temp.size()!=0)
                all_valid_moves.push_back(vector<int>{i,j});
        }
    }
    return all_valid_moves;
}
vector<vector<int>> Game2Grid:: ValidMove(int x, int y){
    vector<vector<int>> can_flip_total;
    for (int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if (i==0 && j==0)
                continue;
            vector<vector<int>> temp_result = this->ExplorePath(x,y,i,j);
            if (temp_result.size()!=0)
                std::copy(temp_result.begin(),temp_result.end(),back_inserter(can_flip_total));
        }
    }
    return can_flip_total;
}

vector<vector<int>> Game2Grid::ExplorePath(int x0,int y0,int x_direction,int y_direction){
    vector<vector<int>> can_flip;
    int i = x0+x_direction;
    int j = y0+y_direction;

    while (i>=0 && i<8 && j>=0 && j<8){
        if (this->Cells->at(i*8+j)->DiscIsPlaced()){
            if (this->Cells->at(i*8+j)->current_color!=Game2Grid::turn)
                can_flip.push_back(vector<int>{i,j});
            else
                return can_flip;
        }
        else {
            can_flip.clear();
            return can_flip;
        }
        i+=x_direction;
        j+=y_direction;
    }
    can_flip.clear();
    return can_flip;
}

void Game2Grid::PressBack(){
    emit(gameOver());
}
