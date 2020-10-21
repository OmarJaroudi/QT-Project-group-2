#include "game1grid.h"
#include <QDebug>
game1grid::game1grid()
{

    setBackgroundBrush(QBrush(QColor::fromRgb(128,0,0),Qt::SolidPattern));
    this->setSceneRect(QRectF(0,0,1010,485));

    blue_virus = new VirusObject(VirusObject::BLUE,90);
    yellow_virus = new VirusObject(VirusObject::YELLOW,70);
    green_virus = new VirusObject(VirusObject::GREEN,50);

    QObject::connect(green_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
    QObject::connect(blue_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
    QObject::connect(yellow_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));

    green_virus->move(800,100);
    blue_virus->move(900,100);
    yellow_virus->move(900,200);

    this->addWidget(green_virus);
    this->addWidget(blue_virus);
    this->addWidget(yellow_virus);

    timer_info = new QLabel("00:00");
    timer = new QTimer();
    elapsed_time = 0;
    timer->start(1000);
    timer_info->move(890,50);
    timer_info->setFixedSize(150,40);
    timer_info->setStyleSheet("QLabel {font-size:40px;color:white;background-color: rgba(255, 255, 255, 0);}");
    this->addWidget(timer_info);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTime()));

    score = 0;
    score_info = new QLabel("0");
    score_info->move(500,50);
    score_info->setFixedSize(150,40);
    score_info->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");

    this->addWidget(score_info);

    smashed_virus = new VirusObject();

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/audio/smashed.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    smash_sound = new QMediaPlayer();
    smash_sound->setPlaylist(playlist);

}

void game1grid::ShootVirus(){
    VirusObject * source = qobject_cast<VirusObject*>(sender());
    if (source->isVisible()){
        smash_sound->play();
        source->hide();
        score += source->getScore();
        score_info->setText(QStringLiteral("%1").arg(score));

        smashed_virus->move(source->x(),source->y());
        this->addWidget(smashed_virus);

    }
}

void game1grid::UpdateTime(){
    elapsed_time+=1;
    int sec = int(elapsed_time % 60);
    QString seconds = "";
    QString minutes = "";

    if (int(elapsed_time%60)<10)
        seconds = QStringLiteral("0%2").arg(int(elapsed_time%60));
    else
        seconds = QStringLiteral("%2").arg(int(elapsed_time%60));

    if (int(elapsed_time/60)<10)
        minutes = QStringLiteral("0%1").arg(int(elapsed_time/60));
    else
        minutes = QStringLiteral("%1").arg(int(elapsed_time/60));

    timer_info->setText(minutes + ":" + seconds);
}
