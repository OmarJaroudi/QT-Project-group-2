#include "signupwidget.h"
#include "welcomewidget.h"
#include "mainmenuwidget.h"

SignUpWidget::SignUpWidget(QWidget *parent) : QWidget(parent)
{
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(33,33,35);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));
    Browser = new BrowseFiles();

    QFont f;
    f.setPointSize(15);

    errorMessage = new QLabel(" ");
    errorMessage->setAlignment(Qt::AlignHCenter);
    errorMessage->setStyleSheet("color:red");

    this->setWindowTitle("Sign up");
    this->setMinimumSize(200,300);

    Prompt= new QLabel("Enter Your Information");
    Prompt->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    FirstName= new QLabel("First Name");
    FirstName->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    LastName= new QLabel("Last Name");
    LastName->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    Username= new QLabel("Username");
    Username->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    Email= new QLabel("Email");
    Email->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    Password= new QLabel("Password");
    Password->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    ConfirmPassword= new QLabel("Confirm Password");
    ConfirmPassword->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    BirthDate= new QLabel("Date of Birth");
    BirthDate->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    ProfilePic= new QLabel("Profile Picture");
    ProfilePic->setStyleSheet(QString("QLabel {font-size:20px; color: %1 ;}").arg(col.name()));

    FirstNameBox= new QLineEdit();
    FirstNameBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    LastNameBox= new QLineEdit();
    LastNameBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    UsernameBox= new QLineEdit();
    UsernameBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    EmailBox= new QLineEdit();
    EmailBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    PasswordBox=new QLineEdit();
    PasswordBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");
    PasswordBox->setEchoMode(QLineEdit::Password);

    ConfirmPasswordBox= new QLineEdit();
    ConfirmPasswordBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");
    ConfirmPasswordBox->setEchoMode(QLineEdit::Password);

    Create= new QPushButton("Create Account");
    Create->setStyleSheet(QString("QPushButton {font-size: 20px; background-color: %1 ;}").arg(col.name()));

    Back = new QPushButton();
    Back->setIcon(QIcon(":/thumbnails/back_button.png"));
    Back->setIconSize(QSize(30, 30));
    Back->setFixedSize(30,30);

    Date= new QDateEdit();
    Date->setStyleSheet("QDateEdit {font-size:20px; background-color: 3px solid white; border-radius:2px;}");
    Date->setMaximumDate(QDate::currentDate());
    Date->setDisplayFormat("dd/MM/yyyy");

    ChoosePic= new QPushButton("Browse");
    ChoosePic->setStyleSheet(QString("QPushButton {font-size: 20px; background-color: %1 ;}").arg(col.name()));

    Grid= new QGridLayout();

    Grid->addWidget(Prompt,0,0,1,3,Qt::AlignHCenter);
    Grid->addWidget(FirstName,1,0);
    Grid->addWidget(FirstNameBox,1,1);
    Grid->addWidget(LastName,2,0);
    Grid->addWidget(LastNameBox,2,1);
    Grid->addWidget(Username,3,0);
    Grid->addWidget(UsernameBox,3,1);
    Grid->addWidget(Email,4,0);
    Grid->addWidget(EmailBox,4,1);
    Grid->addWidget(Password,5,0);
    Grid->addWidget(PasswordBox,5,1);
    Grid->addWidget(ConfirmPassword,6,0);
    Grid->addWidget(ConfirmPasswordBox,6,1);
    Grid->addWidget(BirthDate,7,0);
    Grid->addWidget(Date,7,1);
    Grid->addWidget(ProfilePic,8,0);
    Grid->addWidget(ChoosePic,8,1);
    Grid->addItem(new QSpacerItem(50,15),9,0);
    Grid->addWidget(Create,10,0,1,2,Qt::AlignHCenter);
    Grid->addWidget(Back,11,0);
    Grid->addWidget(errorMessage,11,0,1,3,Qt::AlignHCenter);

    this->setLayout(Grid);

    QObject::connect(ChoosePic,SIGNAL(clicked()),this,SLOT(BrowseForImage()));
    QObject::connect(Back,SIGNAL(clicked()),this,SLOT(ClickReturn()));
    QObject::connect(Create,SIGNAL(clicked()),this,SLOT(CreateAccount()));

}

void SignUpWidget::BrowseForImage(){
    Browser->Disp->show();
}

void SignUpWidget::CreateAccount(){
    errorMessage->clear();
    QString userStr = UsernameBox->text();
    QString passStr = PasswordBox->text();
    QString emailStr = EmailBox->text();
    QString fNameStr = FirstNameBox->text();
    QString lNameStr = LastNameBox->text();
    QString confirmPassStr = ConfirmPasswordBox->text();
    QString dateStr = Date->text();
    QString imgDirectory = Browser->directory;
    Accounts * acc = new Accounts(userStr,passStr,confirmPassStr,dateStr,emailStr,fNameStr,lNameStr,imgDirectory);
    QString result = acc->attemptSignUp();
    if (result!="success")
        errorMessage->setText(result);
    else {
        this->close();
        MainMenuWidget *menu = new MainMenuWidget();
        menu->prepareMenu(acc);
    }

}
void SignUpWidget:: ClickReturn()
{
    this->close();
    WelcomeWidget * scene = new WelcomeWidget();
    scene->setMinimumSize(300,300);
    scene->show();
}




