//#include "historywidget.h"

//historyWidget::historyWidget(Accounts * curr,QWidget *parent) : QWidget(parent)
//{
//    this->setFixedSize(300,300);
//    this->setAttribute(Qt::WA_DeleteOnClose);

//    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
//    this->move(-500000,-500000);
//    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
//               (primaryScreenGeometry.height() - this->height()) / 2.0);

//    //setting background color
//    QColor col = QColor::fromRgb(148,0,211);
//    QColor backgroundColor = QColor::fromRgb(33,33,35);
//    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

//    switchGames= new QPushButton("Switch Games");


//    QVector<QString> userdata1={"","",""};
//    QVector<QString> leaderboard1={"","","","","","","","","","","","","","",""};
//    int i=0;
//    QString path1 = qApp->applicationDirPath();
//    path1.append("/userData/game_1_history.txt");
//    QFile inputFile1(path1);
//    inputFile1.open(QIODevice::ReadOnly);
//    QTextStream stream1(&inputFile1);
//    if (inputFile1.size()!=0){
//        QString line = stream1.readLine();
//        while (line!="") {
//            QStringList tempLine = line.split(" ");

//            leaderboard1[i]=tempLine[0];
//            leaderboard1[i+1]=tempLine[1];
//            leaderboard1[i+2]=tempLine[2];
//            i+=3;

//            if(curr->GetUsername()==tempLine[0])
//            {
//                userdata1[0]=tempLine[0];
//                userdata1[1]=tempLine[1];
//                userdata1[2]=tempLine[2];
//            }
//            QString line = stream1.readLine();
//        }
//    }
//    inputFile1.close();


//    QVector<QString> userdata2={"","",""};
//    QVector<QString> leaderboard2={"","","","","","","","","","","","","","",""};
//    i=0;
//    QString path2 = qApp->applicationDirPath();
//    path1.append("/userData/game_1_history.txt");
//    QFile inputFile2(path1);
//    inputFile1.open(QIODevice::ReadOnly);
//    QTextStream stream2(&inputFile1);
//    if (inputFile1.size()!=0){
//        QString line = stream1.readLine();
//        while (line!="") {
//            QStringList tempLine = line.split(" ");

//            leaderboard2[i]=tempLine[0];
//            leaderboard2[i+1]=tempLine[1];
//            leaderboard2[i+2]=tempLine[2];
//            i+=3;

//            if(curr->GetUsername()==tempLine[0])
//            {
//                userdata2[0]=tempLine[0];
//                userdata2[1]=tempLine[1];
//                userdata2[2]=tempLine[2];
//            }
//            QString line = stream1.readLine();
//        }
//    }
//    inputFile1.close();



//    if(curr->GetUsername()=="Guest player")
//    {
//        highscoreLabel1 = new QLabel("Please Sign up to use this feature.");
//        highscoreLabel2 = new QLabel("");
//    }
//    else{
//        highscoreLabel1 = new QLabel("Youre highscore in game 1 is"+userdata1[1]);
//        highscoreLabel2 = new QLabel("Highscore obtained on"+userdata1[2]);
//    }






//}
