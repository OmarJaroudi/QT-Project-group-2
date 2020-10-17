#include "signupwidget.h"
#include "welcomewidget.h"
#include "mainmenuwidget.h"

SignUpWidget::SignUpWidget(QWidget *parent) : QWidget(parent)
{
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);
    //setting up Widgets
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(33,33,35);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));
    browser = new BrowseFiles();

    QFont f;
    f.setPointSize(15);

    error_message = new QLabel(" ");
    error_message->setAlignment(Qt::AlignHCenter);
    error_message->setStyleSheet("color:red");

    this->setWindowTitle("Sign up");
    this->setMinimumSize(200,300);

    prompt= new QLabel("Enter Your Information");
    prompt->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    first_name= new QLabel("First Name");
    first_name->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    last_name= new QLabel("Last Name");
    last_name->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    username= new QLabel("Username");
    username->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    email= new QLabel("Email");
    email->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    password= new QLabel("Password");
    password->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    confirm_password= new QLabel("Confirm Password");
    confirm_password->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    birth_date= new QLabel("Date of Birth");
    birth_date->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    profile_pic= new QLabel("Profile Picture");
    profile_pic->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    first_name_box= new QLineEdit();
    first_name_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    last_name_box= new QLineEdit();
    last_name_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    username_box= new QLineEdit();
    username_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    email_box= new QLineEdit();
    email_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    password_box=new QLineEdit();
    password_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");
    password_box->setEchoMode(QLineEdit::Password);

    confirm_password_box= new QLineEdit();
    confirm_password_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");
    confirm_password_box->setEchoMode(QLineEdit::Password);

    create= new QPushButton("Create Account");
    create->setStyleSheet(QString("QPushButton {font-size: 20px; background-color: %1 ;}").arg(col.name()));

    back_button = new QPushButton();
    back_button->setIcon(QIcon(":/thumbnails/back_button.png"));
    back_button->setIconSize(QSize(30, 30));
    back_button->setFixedSize(30,30);

    date= new QDateEdit();
    date->setStyleSheet("QDateEdit {font-size:20px; background-color: 3px solid white; border-radius:2px;}");
    date->setMaximumDate(QDate::currentDate());
    date->setDisplayFormat("dd/MM/yyyy");

    choose_pic= new QPushButton("Browse");
    choose_pic->setStyleSheet(QString("QPushButton {font-size: 20px; background-color: %1 ;}").arg(col.name()));

    grid= new QGridLayout();

    //add widgets to a grid and display it
    grid->addWidget(prompt,0,0,1,3,Qt::AlignHCenter);
    grid->addWidget(first_name,1,0);
    grid->addWidget(first_name_box,1,1);
    grid->addWidget(last_name,2,0);
    grid->addWidget(last_name_box,2,1);
    grid->addWidget(username,3,0);
    grid->addWidget(username_box,3,1);
    grid->addWidget(email,4,0);
    grid->addWidget(email_box,4,1);
    grid->addWidget(password,5,0);
    grid->addWidget(password_box,5,1);
    grid->addWidget(confirm_password,6,0);
    grid->addWidget(confirm_password_box,6,1);
    grid->addWidget(birth_date,7,0);
    grid->addWidget(date,7,1);
    grid->addWidget(profile_pic,8,0);
    grid->addWidget(choose_pic,8,1);
    grid->addItem(new QSpacerItem(50,15),9,0);
    grid->addWidget(create,10,0,1,2,Qt::AlignHCenter);
    grid->addWidget(back_button,11,0);
    grid->addWidget(error_message,11,0,1,3,Qt::AlignHCenter);

    this->setLayout(grid);

    //setting up signal slot connections
    QObject::connect(choose_pic,SIGNAL(clicked()),this,SLOT(BrowseForImage()));
    QObject::connect(back_button,SIGNAL(clicked()),this,SLOT(ClickReturn()));
    QObject::connect(create,SIGNAL(clicked()),this,SLOT(CreateAccount()));

}

void SignUpWidget::BrowseForImage(){ //opens up the browser widget
    browser->disp->show();
}

void SignUpWidget::CreateAccount(){//passes the info entered into an instance of account. Attempts sign up.
    error_message->clear();
    QString userStr = username_box->text();
    QString passStr = password_box->text();
    QString emailStr = email_box->text();
    QString fNameStr = first_name_box->text();
    QString lNameStr = last_name_box->text();
    QString confirmPassStr = confirm_password_box->text();
    QString dateStr = date->text();
    QString imgDirectory = browser->directory;
    Accounts * acc = new Accounts(userStr,passStr,confirmPassStr,dateStr,emailStr,fNameStr,lNameStr,imgDirectory);
    QString result = acc->AttemptSignUp();
    if (result!="success")//sign up failed, show error message
        error_message->setText(result);
    else {//sign up succeeded, transition to main menu
        this->close();
        MainMenuWidget *menu = new MainMenuWidget();
        menu->PrepareMenu(acc);
    }

}
void SignUpWidget:: ClickReturn()//return to welcome screen if return button clicked
{
    this->close();
    WelcomeWidget * scene = new WelcomeWidget();
    scene->setMinimumSize(300,300);
    scene->show();
}




