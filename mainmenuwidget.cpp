#include "mainmenuwidget.h" //test push
MainMenuWidget::MainMenuWidget(Accounts *curr,QWidget *parent) : QWidget(parent)
{
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);
    birthday = new QLabel("");
    QSizePolicy sp_retain = birthday->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    birthday->setSizePolicy(sp_retain); //steps made to ensure that "Happy Birthday" blinking wont disrupt the

    game_1_button = new QPushButton("Game 1");
    this-> setWindowTitle("Main Menu");
    this->setMinimumSize(400,400); //ensure proper size of window

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(Blink())); //make happy birthday blink

    current_user = curr;//loads in current user

    log = new QLabel(this->current_user->GetUsername() + "!");
    QFont Font1;
    Font1.setBold(true);
    Font1.setPointSize(12);

    grid = new QGridLayout();
    Logout= new QPushButton("Logout");
    Logout->setFixedSize(80,20);
    grid->addWidget(Logout,0,0);
    img = new QLabel();
    img->setPixmap(QPixmap(this->current_user->GetImgPath()).scaled(150,200));
    img->setScaledContents(true);
    img->setMaximumSize(150,200); //loads in the account's image and sets parameteres
    bigSpacer= new QSpacerItem(175, 0);
    grid->addItem(bigSpacer,1,0);
    grid->addItem(bigSpacer,1,2);
    grid->addWidget(img,1,1);
    Welcome= new QLabel("Welcome");
    log->setFont(Font1);
    Welcome->setFont(Font1);
//    grid->addWidget(Welcome,2,1,Qt::AlignCenter);
//    grid->addItem(bigSpacer,2,0);
//    grid->addItem(bigSpacer,2,2);
//    grid->addWidget(log,3,1,Qt::AlignCenter);
//    grid->addItem(new QSpacerItem(150,0),3,0);
//    grid->addItem(new QSpacerItem(150,0),3,2);



    QDateEdit *currDate = new QDateEdit(QDate::currentDate());//get current date
    currDate->setDisplayFormat("dd/MM/yyyy");
    QString todayDate = currDate->text();//define current date as a string

    bool IsBirthday=true;
    for(int i=0;i<todayDate.length()-4;i++)
    {
        if(todayDate[i]!=this->current_user->GetDOB()[i])
        {
            IsBirthday=false; //checks if birthday and todays date have equal day and month
        }
    }

    vbox = new QVBoxLayout();
    vbox->addItem(grid);
    Welcome->setAlignment(Qt::AlignCenter);
    log->setAlignment(Qt::AlignCenter);
    vbox->addWidget(Welcome);
    vbox->addWidget(log);

    if (IsBirthday){
        birthday->setText("HAPPY BIRTHDAY!!!");//set the value of birthday
        timer->start(750);//start timer
        birthday->setStyleSheet("QLabel { color : red; }");//change color to red
        QFont font =birthday->font();
        font.setBold(true);//set bold
        font.setPointSize(18);//change font size
        birthday->setFont(font);//set font
        birthday->setAlignment(Qt::AlignCenter);
        vbox->addWidget(birthday);//add happy birthday message to the screen
    }



    vbox->addItem(new QSpacerItem(0,20));
    gameGrid= new QGridLayout;
    Game1Label=new ClickableLabel();
    Game1Label->setPixmap(QPixmap(":/thumbnails/game1.PNG").scaled(200,150));
    Game1Label->setFixedSize(200,150);
    gameGrid->addWidget(Game1Label,0,0);
    gameGrid->addItem(new QSpacerItem(200,150),0,1);
    vbox->addItem(gameGrid);

    vbox ->addWidget(game_1_button);
    this->setLayout(vbox);
    this->setStyleSheet("QWidget { background-color : grey }");//set background color to grey
    this->show();

    QObject::connect(Game1Label,SIGNAL(clicked()),this,SLOT(PlayGame1()));


}

void MainMenuWidget::Blink(){//function that hides and then shows the label every timer cycle
    if (birthday->isVisible())
        birthday->hide();
    else
        birthday->show();
}

/**
 * @brief redirect user to new window to start playing game 1
 *
 * create a new instance of game1 class
 */
void MainMenuWidget::PlayGame1(){
    Game1 * game1 = new Game1(current_user);
    game1->show();
    this->hide();

}
