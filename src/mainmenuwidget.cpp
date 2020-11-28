#include "mainmenuwidget.h"
#include "welcomewidget.h"

MainMenuWidget::MainMenuWidget(Accounts *curr,QWidget *parent) : QWidget(parent)
{
    //this->setAttribute(Qt::WA_DeleteOnClose);
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);
    birthday = new QLabel("");
    QSizePolicy sp_retain = birthday->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    birthday->setSizePolicy(sp_retain); //steps made to ensure that "Happy Birthday" blinking wont disrupt the

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
    logout= new QPushButton("Logout");
    logout->setFixedSize(80,20);
    grid->addWidget(logout,0,0);
    img = new QLabel();
    img->setPixmap(QPixmap(this->current_user->GetImgPath()).scaled(150,200));
    img->setScaledContents(true);
    img->setMaximumSize(150,200); //loads in the account's image and sets parameteres
    bigSpacer= new QSpacerItem(175, 0);
    grid->addItem(bigSpacer,1,0);
    grid->addItem(bigSpacer,1,2);
    grid->addWidget(img,1,1);
    welcome= new QLabel("Welcome");
    log->setFont(Font1);
    welcome->setFont(Font1);




    QDateEdit *curr_date = new QDateEdit(QDate::currentDate());//get current date
    curr_date->setDisplayFormat("dd/MM/yyyy");
    QString todayDate = curr_date->text();//define current date as a string

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
    welcome->setAlignment(Qt::AlignCenter);
    log->setAlignment(Qt::AlignCenter);
    vbox->addWidget(welcome);
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
    game_grid= new QGridLayout;
    game_1_label=new ClickableLabel();
    game_1_label->setPixmap(QPixmap(":/thumbnails/game1.PNG").scaled(200,150));
    game_1_label->setFixedSize(200,150);
    game_grid->addWidget(game_1_label,0,0);

    game_2_label=new ClickableLabel();
    game_2_label->setPixmap(QPixmap(":/thumbnails/game2.jpg").scaled(200,150));
    game_2_label->setFixedSize(200,150);
    game_grid->addWidget(game_2_label,0,2);
    vbox->addItem(game_grid);

    history= new QPushButton("Highscores and Leaderboards");
    vbox->addWidget(history);

    this->setLayout(vbox);
    this->setStyleSheet("QWidget { background-color : grey }");//set background color to grey
    this->show();

    QObject::connect(game_1_label,SIGNAL(clicked()),this,SLOT(PlayGame1()));
    QObject::connect(game_2_label,SIGNAL(clicked()),this,SLOT(PlayGame2()));

    QObject::connect(logout,SIGNAL(clicked()),this,SLOT(LogOut()));
    QObject::connect(history,SIGNAL(clicked()),this,SLOT(HistoryClicked()));



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
    Accounts *temp = new Accounts(*(current_user));
    Game1 * game1 = new Game1(temp);
    game1->show();
    this->close();
}

void MainMenuWidget::PlayGame2(){
    Accounts *temp = new Accounts(*(current_user));
    Game2 * game2 = new Game2(temp);
    game2->show();
    this->close();
}

void MainMenuWidget::LogOut(){
    delete current_user;
    WelcomeWidget *welcome = new WelcomeWidget();
    welcome->show();
    this->close();
}

void MainMenuWidget::HistoryClicked(){
    if(current_user->GetUsername()!="Guest player")
    {
        historyWidget *HL = new historyWidget(current_user);
        HL->show();
    }
    else
    {
        Accounts * guestAcc = new Accounts("Guest player","","","","","","",":/thumbnails/blank_profile.png");
        historyWidget *HL = new historyWidget(guestAcc);
        HL->show();
    }

}
