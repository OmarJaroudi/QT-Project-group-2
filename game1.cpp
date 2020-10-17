#include "game1.h"

Game1::Game1(Accounts *acc, QWidget *parent) : QWidget(parent)
{
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);

    QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(QPixmap(":/thumbnails/game1.PNG").scaled(// Scale the background image.
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));             // Use smooth zoom
        this->setPalette(palette);
    this->setWindowTitle("Kill COVID");
    playButton = new QPushButton();
    QPixmap pixMap;
    pixMap.load(":/thumbnails/green_play_button.png");
    playButton->setIcon(pixMap);
    playButton->setIconSize(QSize(75, 75));
    playButton->setFixedSize(75,75);
    playButton->setStyleSheet("QPushButton {color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;}");

    /*QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/backgroundmusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();*/

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(playButton,0,0,Qt::AlignHCenter|Qt::AlignBottom);
    this->setLayout(grid);

    player = acc;
    this->setFixedSize(this->size());

    QObject::connect(playButton,SIGNAL(clicked()),this,SLOT(hide()));


}

void Game1::keyPressEvent(QKeyEvent * event){
    if(event->key() == Qt::Key_F1)
        this->hide();
}
