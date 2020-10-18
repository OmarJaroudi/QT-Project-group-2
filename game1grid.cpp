#include "game1grid.h"

game1grid::game1grid()
{
    QPen line = (QPen(QColor::fromRgb(42,46,51)));
    line.setWidth(10);
    this->setSceneRect(0,0,1000,400);
    for (int x=0; x<=1000;x+=100)
        this->addLine(x,0,x,10000,line);

    // Now add the horizontal lines, paint them green
    for (int y=0; y<=400; y+=100)
        this->addLine(0,y,1000,y, line);

    setBackgroundBrush(QBrush(QColor::fromRgb(128,0,0),Qt::SolidPattern));

    blue_virus=new ClickableLabel();
    blue_virus->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
    blue_virus->setPixmap(QPixmap(":/thumbnails/blue_.png").scaled(85,85));
    blue_virus->setFixedSize(85,85);

    yellow_virus=new ClickableLabel();
    yellow_virus->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
    yellow_virus->setPixmap(QPixmap(":/thumbnails/yellow.png").scaled(75,75));
    yellow_virus->setFixedSize(75,75);

    green_virus=new ClickableLabel();
    green_virus->setStyleSheet("QLabel {background-color: rgba(255, 255, 255, 0);}");
    green_virus->setPixmap(QPixmap(":/thumbnails/green.png").scaled(65,65));
    green_virus->setFixedSize(65,65);

    green_virus->move(918,218);
    blue_virus->move(808,208);
    yellow_virus->move(713,213);

    this->addWidget(green_virus);
    this->addWidget(blue_virus);
    this->addWidget(yellow_virus);

    QObject::connect(green_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
    QObject::connect(blue_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
    QObject::connect(yellow_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));

}

void game1grid::ShootVirus(){
    QLabel * source = qobject_cast<QLabel*>(sender());
    if (source->isVisible())
        source->hide();
}
