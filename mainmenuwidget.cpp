#include "mainmenuwidget.h" //test push
MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent)
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
}
void MainMenuWidget::PrepareMenu(Accounts * curr)
{
    current_user = curr;//loads in current user

    log = new QLabel("Welcome " + this->current_user->GetUsername() + "!");

    grid = new QGridLayout();
    grid->addWidget(log,0,0);//shows welcome username
    img = new QLabel();

    img->setPixmap(QPixmap(this->current_user->GetImgPath()).scaled(50,50));
    img->setScaledContents(true);
    img->setMaximumSize(125,125); //loads in the account's image and sets parameteres

    grid->addWidget(img,1,1);
    QDateEdit *currDate = new QDateEdit(QDate::currentDate());//get current date
    currDate->setDisplayFormat("dd/MM/yyyy");
    QString todayDate = currDate->text();//define current date as a string
    current_date_label= new QLabel(todayDate);
    grid->addWidget(current_date_label,0,1);//display today's date on top right

    bool IsBirthday=true;
    for(int i=0;i<todayDate.length()-4;i++)
    {
        if(todayDate[i]!=this->current_user->GetDOB()[i])
        {
            IsBirthday=false; //checks if birthday and todays date have equal day and month
        }
    }
    if (IsBirthday){
        birthday->setText("HAPPY BIRTHDAY!!!");//set the value of birthday
        timer->start(750);//start timer
        birthday->setStyleSheet("QLabel { color : red; }");//change color to red
        QFont font =birthday->font();
        font.setBold(true);//set bold
        font.setPointSize(14);//change font size
        birthday->setFont(font);//set font
        grid->addWidget(birthday,1,0);//add happy birthday message to the screen
    }

    vbox = new QVBoxLayout();
    vbox->addItem(grid);
    vbox->addItem(new QSpacerItem(200,200));//space to add games later on
    vbox ->addWidget(game_1_button);
    this->setLayout(vbox);
    this->setStyleSheet("QWidget { background-color : grey }");//set background color to grey
    this->show();

    QObject::connect(game_1_button,SIGNAL(clicked()),this,SLOT(PlayGame1()));

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
    this->hide();
    game1->show();
}
