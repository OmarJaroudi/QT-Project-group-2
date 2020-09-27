#include "mainmenuwidget.h" //test push
//OMAR JAROUDI
MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent)
{
    birthday = new QLabel("");
    QSizePolicy sp_retain = birthday->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    birthday->setSizePolicy(sp_retain);

    this-> setWindowTitle("Main Menu");
    this->setMinimumSize(400,400);

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(blink()));
}
void MainMenuWidget::prepareMenu(Accounts * curr)
{
    currentUser = curr;

    log = new QLabel("Welcome " + this->currentUser->getUsername() + "!");

    grid = new QGridLayout();
    grid->addWidget(log,0,2);
    img = new QLabel();

    img->setPixmap(QPixmap(this->currentUser->getImgPath()).scaled(50,50));

    grid->addWidget(img,0,0);
    QDateEdit *currDate = new QDateEdit(QDate::currentDate());
    currDate->setDisplayFormat("dd/MM/yyyy");
    QString todayDate = currDate->text();
    if (todayDate == this->currentUser->getDOB()){
        birthday->setText("HAPPY BIRTHDAY!!!");
        timer->start(750);
        grid->addWidget(birthday,1,2);
    }

    this->setLayout(grid);
    this->show();
}

void MainMenuWidget::blink(){
    if (birthday->isVisible())
        birthday->hide();
    else
        birthday->show();
}
