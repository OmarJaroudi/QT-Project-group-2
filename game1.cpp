#include "game1.h"

Game1::Game1(Accounts *acc, QWidget *parent) : QWidget(parent)
{
    player = acc;
    easy  =new QPushButton("easy");
    medium = new QPushButton("medium");
    hard = new QPushButton("hard");

    back_button = new QPushButton();

    back_button->setIcon(QIcon(":/thumbnails/back_button.png"));
    back_button->setIconSize(QSize(30, 30));
    back_button->setFixedSize(30,30);


    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);

    QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(QPixmap(":/thumbnails/game1.PNG").scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
    this->setWindowTitle("Kill COVID-19");
    play_button = new QPushButton();
    QPixmap pixMap;
    pixMap.load(":/thumbnails/green_play_button.png");
    play_button->setIcon(pixMap);
    play_button->setIconSize(QSize(75, 75));
    play_button->setFixedSize(75,75);
    play_button->setStyleSheet("QPushButton {color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;}");

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/audio/GTA_san_andreas.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    QSpacerItem *spacer = new QSpacerItem(300,400, QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout = new QVBoxLayout();
    layout->addItem(spacer);

    layout->addWidget(play_button,100,Qt::AlignHCenter|Qt::AlignBottom);
    layout->addWidget(back_button,30,Qt::AlignLeft|Qt::AlignBottom);

    this->setLayout(layout);

    this->setFixedSize(this->size());

    QObject::connect(play_button,SIGNAL(clicked()),this,SLOT(ChooseDifficulty()));

    QObject::connect(back_button,SIGNAL(clicked()),this,SLOT(PressBack()));

    QObject::connect(easy,SIGNAL(clicked()),this,SLOT(StartGame()));
    QObject::connect(medium,SIGNAL(clicked()),this,SLOT(StartGame()));
    QObject::connect(hard,SIGNAL(clicked()),this,SLOT(StartGame()));

}

void Game1::keyPressEvent(QKeyEvent * event){
    if(event->key() == Qt::Key_F1)
        ChooseDifficulty();
}

void Game1::ChooseDifficulty(){

    delete play_button;
    delete layout;
    QSpacerItem *spacer = new QSpacerItem(300,400, QSizePolicy::Expanding, QSizePolicy::Fixed);

    difficulty_layout = new QVBoxLayout();
    difficulty_layout->addItem(spacer);
    difficulty_layout->addWidget(easy,200,Qt::AlignCenter);
    difficulty_layout->addWidget(medium,200,Qt::AlignCenter);
    difficulty_layout->addWidget(hard,200,Qt::AlignCenter);
    //difficultyLayout->addWidget(Back,30,Qt::AlignLeft|Qt::AlignBottom);
    this->setLayout(difficulty_layout);
}
void Game1::PressBack(){
    this->close();
    delete this;
    MainMenuWidget * main_menu = new MainMenuWidget(this->player);
    main_menu->show();
}
void Game1::StartGame(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    QString buttonText = buttonSender->text();

}
