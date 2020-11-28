#include "reversislot.h"

ReversiSlot::ReversiSlot(int x, int y){
    this->setStyleSheet("QPushButton {background-color:rgb(4,140,4)}");
    this->setFixedSize(50,50);
    this->setIconSize(QSize(100,100));
    is_placed = false;
    this->x=x;
    this->y=y;
}

bool ReversiSlot::DiscIsPlaced(){
    return this->is_placed;
}

void ReversiSlot::PlaceDisc(ReversiSlot::COLOR color){
    if(color==ReversiSlot::WHITE){
        QIcon checker(QPixmap(":/thumbnails/white_checker.png").scaled(45,45));
        this->setIcon(checker);
        current_color=color;
    }
    else {
        QIcon checker(QPixmap(":/thumbnails/black_checker.png").scaled(45,45));
        this->setIcon(checker);
        current_color=color;
    }
    this->is_placed = true;
}

void ReversiSlot::Flip(){
    if (this->current_color==ReversiSlot::WHITE)
        this->PlaceDisc(ReversiSlot::BLACK);
    else
        this->PlaceDisc(ReversiSlot::WHITE);
}
