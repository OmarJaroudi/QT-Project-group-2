#include "virusobject.h"

bool VirusObject::recent_miss = false;
int VirusObject::total_misses = 0;
VirusObject::Color VirusObject::missed_color = VirusObject::GREEN;

VirusObject::VirusObject(){
    this->setPixmap(QPixmap(":/thumbnails/smashed.png").scaled(60,60));
    this->setFixedSize(60,60);
    this->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
}

VirusObject::VirusObject(VirusObject::Color c)
{
    this->color = c;

    QString pix_map = "";
    if (c==VirusObject::GREEN){
        this->score = 3;
        pix_map = ":/thumbnails/green.png";
        this->size = 50;
    }
    else if (c==VirusObject::YELLOW){
        this->score = 5;
        pix_map = ":/thumbnails/yellow.png";
        this->size = 70;
    }
    else{
        this->score = 7;
        pix_map = ":/thumbnails/blue_.png";
        this->size = 90;
    }
    this->setPixmap(QPixmap(pix_map).scaled(size,size));
    this->setFixedSize(size,size);
    this->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/audio/smashed.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    smash_sound = new QMediaPlayer();
    smash_sound->setPlaylist(playlist);

    expiry_timer = new QTimer();
    QObject::connect(expiry_timer,SIGNAL(timeout()),this,SLOT(Expire()));
    expiry_timer->start(1500);


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

void VirusObject:: Expire(){

    if(this->isVisible()){
        qDebug()<<"MISS";
        recent_miss = true;
        total_misses+=1;
        missed_color = this->color;
    }
    delete this;

}
