#include "virusobject.h"


VirusObject::VirusObject(){
    this->setPixmap(QPixmap(":/thumbnails/smashed.png").scaled(60,60));
    this->setFixedSize(60,60);
    this->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
}

VirusObject::VirusObject(VirusObject::Color c,int size)
{
    this->color = c;
    this->size = size;
    QString pix_map = "";
    if (c==VirusObject::GREEN){
        this->score = 3;
        pix_map = ":/thumbnails/green.png";
    }
    else if (c==VirusObject::YELLOW){
        this->score = 5;
        pix_map = ":/thumbnails/yellow.png";
    }
    else{
        this->score = 7;
        pix_map = ":/thumbnails/blue_.png";
    }
    this->setPixmap(QPixmap(pix_map).scaled(size,size));
    this->setFixedSize(size,size);
    this->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
}
QString VirusObject::getColor(){
    QString c;
    switch(this->color) {
    case GREEN: c = "green";
        break;
    case BLUE: c = "blue";
        break;
    case YELLOW: c = "yellow";
        break;
    }
    return c;
}

int VirusObject::getScore(){
    return this->score;
}
int VirusObject::getSize(){
    return this->size;
}
