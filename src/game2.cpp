#include "game2.h"

Game2::Game2(Accounts *acc, QWidget *parent) : QWidget(parent)
{
    player = acc;
    player2Name = new QLineEdit();
    back_button = new QPushButton();
    error = new QLabel("Enter player 2 name");
    error->setStyleSheet("QLabel {color:white;}");
    pick_white = new QRadioButton("Player 2 is white");
    pick_white->setStyleSheet("QRadioButton {color:red;}");

    pick_black = new QRadioButton("Player 2 is black");
    pick_black->setStyleSheet("QRadioButton {color:red;}");
    back_button->setIcon(QIcon(":/thumbnails/back_button.png"));
    back_button->setIconSize(QSize(30, 30));
    back_button->setFixedSize(30,30);

    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);

    QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(QPixmap(":/thumbnails/game2.jpg").scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
    this->setWindowTitle("REVERSI");
    play_button = new QPushButton();

    QPixmap pixMap;
    pixMap.load(":/thumbnails/green_play_button.png");
    play_button->setIcon(pixMap);
    play_button->setIconSize(QSize(75, 75));
    play_button->setFixedSize(75,75);
    play_button->setStyleSheet("QPushButton {color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;}");

    spacer = new QSpacerItem(5,5, QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout = new QHBoxLayout();
    layout->addWidget(back_button,0,Qt::AlignLeft|Qt::AlignBottom);
    layout->addItem(spacer);


    layout->addWidget(play_button,50,Qt::AlignCenter|Qt::AlignBottom);
    v_layout = new QVBoxLayout();
    v_layout->addWidget(player2Name,50,Qt::AlignRight);
    v_layout->addWidget(error,50,Qt::AlignTop|Qt::AlignRight);
    v_layout->addWidget(pick_black,50,Qt::AlignTop|Qt::AlignRight);
    v_layout->addWidget(pick_white,50,Qt::AlignTop|Qt::AlignRight);
    v_layout->addItem(new QSpacerItem(5,400, QSizePolicy::Expanding, QSizePolicy::Fixed));
    v_layout->addItem(layout);
    this->setLayout(v_layout);
    this->setFixedSize(this->size());

    QObject::connect(play_button,SIGNAL(clicked()),this,SLOT(StartGame()));
    QObject::connect(back_button,SIGNAL(clicked()),this,SLOT(PressBack()));

}
void Game2::PressBack(){
    this->close();
    MainMenuWidget * main_menu = new MainMenuWidget(this->player);
    main_menu->show();
    this->deleteLater();
}
void Game2::StartGame(){
    if (player2Name->text()=="" || (!pick_white->isChecked() && !pick_black->isChecked())){
        error->setStyleSheet("QLabel {color:red;}");
        return;
    }
    grid = new Game2Grid();
    this->close();
    view = new QGraphicsView(grid);
    view->setAttribute(Qt::WA_DeleteOnClose);
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    view->move(-500000,-500000);
    view->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);
    view->show();
    view->setFixedSize(400,450);
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setAttribute(Qt::WA_DeleteOnClose);

    view->setWindowTitle("Reversi");
    QObject::connect(grid,SIGNAL(gameOver()),this,SLOT(GameEnded()));
    QObject::connect(grid,SIGNAL(updateScore()),this,SLOT(ScoreUpdated()));

}
void Game2::GameEnded(){
    view->close();
    this->show();
}
void Game2::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_F1)
        StartGame();
}
void Game2::ScoreUpdated()
{
    qDebug()<<grid->int_save_score;
    if (!(this->player->GetUsername()=="Guest player"))
        this->player->UpdateHistory(grid->int_save_score,2);
}


