#include "game1grid.h"
#include <QDebug>
game1grid::game1grid()
{

    /*QPen line = (QPen(QColor::fromRgb(42,46,51)));
    line.setWidth(10);
    for (int x=0; x<=1100;x+=100)
        this->addLine(x,0,x,10000,line);

    // Now add the horizontal lines, paint them green
    for (int y=0; y<=400; y+=100)
        this->addLine(0,y,1000,y, line);

    setBackgroundBrush(QBrush(QColor::fromRgb(128,0,0),Qt::SolidPattern));*/
    this->setBackgroundBrush(QBrush(QPixmap(":/thumbnails/grid.PNG")));
    this->setSceneRect(QRectF(0,0,1010,485));


    blue_virus=new ClickableLabel("blue");
    blue_virus->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
    blue_virus->setPixmap(QPixmap(":/thumbnails/blue_.png").scaled(75,75));
    blue_virus->setFixedSize(75,75);

    yellow_virus=new ClickableLabel("yellow");
    yellow_virus->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
    yellow_virus->setPixmap(QPixmap(":/thumbnails/yellow.png").scaled(65,65));
    yellow_virus->setFixedSize(65,65);

    green_virus=new ClickableLabel("green");
    green_virus->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
    green_virus->setPixmap(QPixmap(":/thumbnails/green.png").scaled(55,55));
    green_virus->setFixedSize(55,55);


    QObject::connect(green_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
    QObject::connect(blue_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
    QObject::connect(yellow_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));

    green_virus->move(930,420);
    blue_virus->move(820,400);
    yellow_virus->move(720,410);

    this->addWidget(green_virus);
    this->addWidget(blue_virus);
    this->addWidget(yellow_virus);

    timer_info = new QLabel("00:00");
    timer = new QTimer();
    elapsed_time = 0;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTime()));
    timer->start(1000);
    timer_info->move(890,50);
    timer_info->setFixedSize(150,40);
    timer_info->setStyleSheet("QLabel {font-size:40px;color:white;background-color: rgba(255, 255, 255, 0);}");
    this->addWidget(timer_info);

    score = 0;
    score_info = new QLabel("0");
    score_info->move(500,40);
    score_info->setFixedSize(150,40);
    score_info->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");

    this->addWidget(score_info);

}

void game1grid::ShootVirus(){
    ClickableLabel * source = qobject_cast<ClickableLabel*>(sender());
    if (source->isVisible()){
        source->hide();
        QString virus = source->color;
        if (virus=="blue")
            score+=7;
        else if (virus=="yellow")
            score+=5;
        else
            score+=3;
        score_info->setText(QStringLiteral("%1").arg(score));
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
