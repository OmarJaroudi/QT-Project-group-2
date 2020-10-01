#include "mainmenuwidget.h" //test push
//OMAR JAROUDI
MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent)
{
    birthday = new QLabel("");
    QSizePolicy sp_retain = birthday->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    birthday->setSizePolicy(sp_retain); //steps made to ensure that "Happy Birthday" blinking wont disrupt the

    this-> setWindowTitle("Main Menu");
    this->setMinimumSize(400,400); //ensure proper size of window

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(blink())); //make happy birthday blink
}
void MainMenuWidget::prepareMenu(Accounts * curr)
{
    currentUser = curr;//loads in current user

    log = new QLabel("Welcome " + this->currentUser->getUsername() + "!");

    grid = new QGridLayout();
    grid->addWidget(log,0,0);//shows welcome username
    img = new QLabel();

    img->setPixmap(QPixmap(this->currentUser->getImgPath()).scaled(50,50));
    img->setScaledContents(true);
    img->setMaximumSize(125,125); //loads in the account's image and sets parameteres

    grid->addWidget(img,1,1);
    QDateEdit *currDate = new QDateEdit(QDate::currentDate());//get current date
    currDate->setDisplayFormat("dd/MM/yyyy");
    QString todayDate = currDate->text();//define current date as a string
    currentDateLabel= new QLabel(todayDate);
    grid->addWidget(currentDateLabel,0,1);//display today's date on top right

    bool IsBirthday=true;
    for(int i=0;i<todayDate.length()-4;i++)
    {
        if(todayDate[i]!=this->currentUser->getDOB()[i])
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

    VBox = new QVBoxLayout();
    VBox->addItem(grid);
    VBox->addItem(new QSpacerItem(200,200));//space to add games later on

    this->setLayout(VBox);
    this->setStyleSheet("QWidget { background-color : grey }");//set background color to grey
    this->show();
}

void MainMenuWidget::blink(){//function that hides and then shows the label every timer cycle
    if (birthday->isVisible())
        birthday->hide();
    else
        birthday->show();
}
