#include "historywidget.h"

historyWidget::historyWidget(Accounts * curr,QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500,200);
    this->setAttribute(Qt::WA_DeleteOnClose);

    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
               (primaryScreenGeometry.height() - this->height()) / 2.0);
    this->setWindowTitle("Highscores and Leaderboards");
    //setting background color
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(134,132,130);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

    switchGames= new QPushButton("Switch Games");
    topButtonBox= new QHBoxLayout();
    topButtonBox->addItem(new QSpacerItem(375,0));
    topButtonBox->addWidget(switchGames);



    QVector<QString> userdata1={"","","","","",""};
    QVector<QString> leaderboard1={"","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""};
    int i=0;
    QString path1 = qApp->applicationDirPath();
    path1.append("/userData/game_1_history.txt");
    QFile inputFile1(path1);
    inputFile1.open(QIODevice::ReadOnly);
    QTextStream stream1(&inputFile1);
    if (inputFile1.size()!=0){
        QString line = stream1.readLine();
        while (line!="") {
            QStringList tempLine = line.split(" ");
            qDebug()<<i;
            leaderboard1[i]=tempLine[0];
            leaderboard1[i+1]=tempLine[1];
            leaderboard1[i+2]=tempLine[2];
            leaderboard1[i+3]=tempLine[3];
            leaderboard1[i+4]=tempLine[4];
            leaderboard1[i+5]=tempLine[5];
            i+=6;

            if(curr->GetUsername()==tempLine[0])
            {
                userdata1[0]=tempLine[0];
                userdata1[1]=tempLine[1];
                userdata1[2]=tempLine[2];
                userdata1[3]=tempLine[3];
                userdata1[4]=tempLine[4];
                userdata1[5]=tempLine[5];
            }
            line = stream1.readLine();
        }
    }
    inputFile1.close();


    QVector<QString> userdata2={"","","","","",""};
    QVector<QString> leaderboard2={"","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""};
    i=0;
    QString path2 = qApp->applicationDirPath();
    path2.append("/userData/game_2_history.txt");
    QFile inputFile2(path2);
    inputFile2.open(QIODevice::ReadOnly);
    QTextStream stream2(&inputFile2);
    if (inputFile2.size()!=0){
        QString line = stream2.readLine();
        while (line!="") {
            QStringList tempLine = line.split(" ");
            qDebug()<<1;
            leaderboard2[i]=tempLine[0];
            leaderboard2[i+1]=tempLine[1];
            leaderboard2[i+2]=tempLine[2];
            leaderboard2[i+3]=tempLine[3];
            leaderboard2[i+4]=tempLine[4];
            leaderboard2[i+5]=tempLine[5];

            i+=6;

            if(curr->GetUsername()==tempLine[0])
            {qDebug()<<"2";
                userdata2[0]=tempLine[0];
                userdata2[1]=tempLine[1];
                userdata2[2]=tempLine[2];
                userdata2[3]=tempLine[3];
                userdata2[4]=tempLine[4];
                userdata2[5]=tempLine[5];
            }
            line=stream2.readLine();
        }
    }
    inputFile2.close();



    if(curr->GetUsername()=="Guest player")
    {
        highscoreLabel1 = new QLabel("Please Sign up to use this feature.");
        highscoreLabel2 = new QLabel("");
        highscoreLabel12 = new QLabel("Please Sign up to use this feature.");
        highscoreLabel22 = new QLabel("");
    }
    else{
        highscoreLabel1 = new QLabel("Youre highscore in game 1 is "+userdata1[1]);
        highscoreLabel2 = new QLabel("Highscore obtained on "+userdata1[2]+" "+userdata1[3]+" "+userdata1[4]+" "+userdata1[5]);
        highscoreLabel12 = new QLabel("Youre highscore in game 2 is "+userdata2[1]);
        highscoreLabel22 = new QLabel("Highscore obtained on "+userdata2[2]+" "+userdata2[3]+" "+userdata2[4]+" "+userdata2[5]);
    }

    rank_header = new QLabel("rank");
    date_header = new QLabel("date and time");
    username_header = new QLabel("username");
    score_header = new QLabel("score");

    rank1= new QLabel("1");
    rank2= new QLabel("2");
    rank3= new QLabel("3");
    rank4= new QLabel("4");
    rank5= new QLabel("5");

    rank_header->setStyleSheet(QString("color: %1").arg(col.name()));
    date_header->setStyleSheet(QString("color: %1").arg(col.name()));
    username_header->setStyleSheet(QString("color: %1").arg(col.name()));
    score_header->setStyleSheet(QString("color: %1").arg(col.name()));

    username_top1= new QLabel(leaderboard1[0]);
    score_top1= new QLabel(leaderboard1[1]);
    date_top1= new QLabel(leaderboard1[3]+" "+leaderboard1[4]+" "+leaderboard1[5]);
    username_top2= new QLabel(leaderboard1[6]);
    score_top2= new QLabel(leaderboard1[7]);
    date_top2= new QLabel(leaderboard1[9]+leaderboard1[10]+" "+leaderboard1[11]);
    username_top3= new QLabel(leaderboard1[12]);
    score_top3= new QLabel(leaderboard1[13]);
    date_top3= new QLabel(leaderboard1[15]+" "+leaderboard1[16]+" "+leaderboard1[17]);
    username_top4= new QLabel(leaderboard1[18]);
    score_top4= new QLabel(leaderboard1[19]);
    date_top4= new QLabel(leaderboard1[21]+" "+leaderboard1[22]+" "+leaderboard1[23]);
    username_top5= new QLabel(leaderboard1[24]);
    score_top5= new QLabel(leaderboard1[25]);
    date_top5= new QLabel(leaderboard1[27]+" "+leaderboard1[28]+" "+leaderboard1[29]);

    Grid1= new QGridLayout();
    Grid1->addWidget(rank_header,0,0);
    Grid1->addWidget(username_header,0,1);
    Grid1->addWidget(score_header,0,2);
    Grid1->addWidget(date_header,0,3);
    Grid1->addWidget(rank1,1,0);
    Grid1->addWidget(username_top1,1,1);
    Grid1->addWidget(score_top1,1,2);
    Grid1->addWidget(date_top1,1,3);
    Grid1->addWidget(rank2,2,0);
    Grid1->addWidget(username_top2,2,1);
    Grid1->addWidget(score_top2,2,2);
    Grid1->addWidget(date_top2,2,3);
    Grid1->addWidget(rank3,3,0);
    Grid1->addWidget(username_top3,3,1);
    Grid1->addWidget(score_top3,3,2);
    Grid1->addWidget(date_top3,3,3);
    Grid1->addWidget(rank4,4,0);
    Grid1->addWidget(username_top4,4,1);
    Grid1->addWidget(score_top4,4,2);
    Grid1->addWidget(date_top4,4,3);
    Grid1->addWidget(rank5,5,0);
    Grid1->addWidget(username_top5,5,1);
    Grid1->addWidget(score_top5,5,2);
    Grid1->addWidget(date_top5,5,3);
    Vbox1= new QVBoxLayout();
    Vbox1->addItem(topButtonBox);
    highscoreLabel1->setAlignment(Qt::AlignCenter);
    Vbox1->addWidget(highscoreLabel1);
    highscoreLabel2->setAlignment(Qt::AlignCenter);
    Vbox1->addWidget(highscoreLabel2);
    Vbox1->addItem(Grid1);



    username_top12= new QLabel(leaderboard2[0]);
    score_top12= new QLabel(leaderboard2[1]);
    date_top12= new QLabel(leaderboard2[3]+" "+leaderboard2[4]+" "+leaderboard2[5]);
    username_top22= new QLabel(leaderboard2[6]);
    score_top22= new QLabel(leaderboard2[7]);
    date_top22= new QLabel(leaderboard2[9]+leaderboard2[10]+" "+leaderboard2[11]);
    username_top32= new QLabel(leaderboard2[12]);
    score_top32= new QLabel(leaderboard2[13]);
    date_top32= new QLabel(leaderboard2[15]+" "+leaderboard2[16]+" "+leaderboard2[17]);
    username_top42= new QLabel(leaderboard2[18]);
    score_top42= new QLabel(leaderboard2[19]);
    date_top42= new QLabel(leaderboard2[21]+" "+leaderboard2[22]+" "+leaderboard2[23]);
    username_top52= new QLabel(leaderboard2[24]);
    score_top52= new QLabel(leaderboard2[25]);
    date_top52= new QLabel(leaderboard2[27]+" "+leaderboard2[28]+" "+leaderboard2[29]);

    Grid2= new QGridLayout();
    Grid2->addWidget(rank_header,0,0);
    Grid2->addWidget(username_header,0,1);
    Grid2->addWidget(score_header,0,2);
    Grid2->addWidget(date_header,0,3);
    Grid2->addWidget(rank1,1,0);
    Grid2->addWidget(username_top12,1,1);
    Grid2->addWidget(score_top12,1,2);
    Grid2->addWidget(date_top12,1,3);
    Grid2->addWidget(rank2,2,0);
    Grid2->addWidget(username_top22,2,1);
    Grid2->addWidget(score_top22,2,2);
    Grid2->addWidget(date_top22,2,3);
    Grid2->addWidget(rank3,3,0);
    Grid2->addWidget(username_top32,3,1);
    Grid2->addWidget(score_top32,3,2);
    Grid2->addWidget(date_top32,3,3);
    Grid2->addWidget(rank4,4,0);
    Grid2->addWidget(username_top42,4,1);
    Grid2->addWidget(score_top42,4,2);
    Grid2->addWidget(date_top42,4,3);
    Grid2->addWidget(rank5,5,0);
    Grid2->addWidget(username_top52,52,1);
    Grid2->addWidget(score_top52,52,2);
    Grid2->addWidget(date_top52,52,3);
    Vbox2= new QVBoxLayout();
    Vbox2->addItem(topButtonBox);
    highscoreLabel12->setAlignment(Qt::AlignCenter);
    Vbox2->addWidget(highscoreLabel12);
    highscoreLabel22->setAlignment(Qt::AlignCenter);
    Vbox2->addWidget(highscoreLabel22);
    Vbox2->addItem(Grid2);

    this->setLayout(Vbox1);

    QObject::connect(switchGames,SIGNAL(clicked()),this,SLOT(changeGame()));

}

void historyWidget::changeGame()
{
    //TODO in phase 3


    /*if(b)
    {
        b=!b;
        delete Grid1;
        this->layout()->update();
    }
    else
    {
        b=!b;
        delete this;
        this->setLayout(Vbox1);
    }*/
}
