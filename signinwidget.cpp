#include "signinwidget.h"
#include "welcomewidget.h"
#include "mainmenuwidget.h"

SignInWidget::SignInWidget(QWidget *parent) : QWidget(parent)
{
    //setting up Widgets
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(33,33,35);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

    errorMessage = new QLabel(" ");
    errorMessage->setAlignment(Qt::AlignHCenter);
    QPalette palette = errorMessage->palette();
    palette.setColor(errorMessage->foregroundRole(),Qt::red);
    errorMessage->setPalette(palette);

    this->setWindowTitle("Sign in");
    this->setMinimumSize(200,300);

    QFont f;
    f.setPointSize(15);

    Back = new QPushButton();

    Back->setIcon(QIcon(":/thumbnails/back_button.png"));
    Back->setIconSize(QSize(30, 30));
    Back->setFixedSize(30,30);

    username = new QLabel("username/email");
    username->setFont(f);
    username->setStyleSheet(QString("color: %1").arg(col.name()));

    password = new QLabel("password");
    password->setFont(f);
    password->setStyleSheet(QString("color: %1").arg(col.name()));

    usernameBox = new QLineEdit;
    usernameBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    passBox = new QLineEdit;
    passBox->setEchoMode(QLineEdit::Password);
    passBox->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    LogIn = new QPushButton("Log in");
    LogIn->setMinimumSize(100,20);
    LogIn->setStyleSheet(QString("QPushButton {font-size: 20px; background-color: %1 ;}").arg(col.name()));
    hbox = new QHBoxLayout();

    //adding widgets to a grid and Hbox
    QGridLayout * grid = new QGridLayout;
    grid->addWidget(username,0,0);
    grid->addWidget(usernameBox,0,1);
    grid->addItem(new QSpacerItem(50, 10), 1, 0,1,2);
    grid->addWidget(password,2,0);
    grid->addWidget(passBox,2,1);
    grid->addItem(new QSpacerItem(50, 10), 3, 0,2,2);

    hbox->addWidget(LogIn);

    grid->addItem(hbox,6,0,1,3,Qt::AlignHCenter);

    //adding the grid and Hbox and widgets to a Vbox which is then displayed
    layout = new QVBoxLayout();
    layout->addItem(grid);
    layout->addWidget(errorMessage);
    layout->addWidget(Back,Qt::AlignLeft | Qt::AlignBottom);


    this->setLayout(layout);

    //signal slot connections
    QObject::connect(Back,SIGNAL(clicked()),this,SLOT(ClickReturn()));
    QObject::connect(LogIn,SIGNAL(clicked()),this,SLOT(verifyCredentials()));
}

void SignInWidget::verifyCredentials(){//passes the input to attemptSignIn.
    QString user = this->usernameBox->text();
    QString pass = this->passBox->text();

    Accounts * acc = new Accounts(user,pass);
    QString result = acc->attemptSignIn();
    if (result!="success")
        errorMessage->setText(result);//failed verification
    else{
        this->close();
        MainMenuWidget *menu = new MainMenuWidget();//verification succes, transitions to mainmenu
        menu->prepareMenu(acc);
    }
}

void SignInWidget:: ClickReturn()//returns the user to the welcome screen if the return button is pushed
{
    this->close();
    WelcomeWidget * scene = new WelcomeWidget();
    scene->setMinimumSize(300,300);
    scene->show();
}
