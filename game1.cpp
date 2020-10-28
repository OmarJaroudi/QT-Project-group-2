#include "game1.h"

Game1::Game1(Accounts *acc, QWidget *parent) : QWidget(parent)
{
    //this->setAttribute(Qt::WA_DeleteOnClose);

    player = acc;
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

    QSpacerItem *spacer = new QSpacerItem(300,400, QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout = new QVBoxLayout();
    layout->addItem(spacer);

    layout->addWidget(play_button,100,Qt::AlignHCenter|Qt::AlignBottom);
    layout->addWidget(back_button,30,Qt::AlignLeft|Qt::AlignBottom);

    this->setLayout(layout);
    this->setFixedSize(this->size());

    QObject::connect(play_button,SIGNAL(clicked()),this,SLOT(StartGame()));
    QObject::connect(back_button,SIGNAL(clicked()),this,SLOT(PressBack()));

}
void Game1::keyPressEvent(QKeyEvent * event){
    if(event->key() == Qt::Key_F1)
        StartGame();
}


void Game1::PressBack(){
    this->close();
    MainMenuWidget * main_menu = new MainMenuWidget(this->player);
    main_menu->show();
}

void Game1::StartGame(){
    VirusObject::recent_miss = false;
    VirusObject::total_misses = 0;
    VirusObject::missed_shots.clear();
    grid = new Game1Grid();
    this->close();
    view = new QGraphicsView(grid);
    view->setAttribute(Qt::WA_DeleteOnClose);
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    view->move(-500000,-500000);
    view->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);
    view->show();
    view->setFixedSize(1010,485);
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(grid,SIGNAL(gameOver()),this,SLOT(GameEnded()));
}

void Game1::GameEnded(){
    qDebug()<<"game over";
    if(grid->save_score) {
        if (!(this->player->GetUsername()=="Guest player"))
            this->player->UpdateHistory(grid->current_score,1);
    }
    view->close();
    this->show();
}
