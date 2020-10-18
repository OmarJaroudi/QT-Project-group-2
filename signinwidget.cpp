#include "signinwidget.h"
#include "welcomewidget.h"
#include "mainmenuwidget.h"

SignInWidget::SignInWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);
    //setting up Widgets
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(33,33,35);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

    error_message = new QLabel(" ");
    error_message->setAlignment(Qt::AlignHCenter);
    QPalette palette = error_message->palette();
    palette.setColor(error_message->foregroundRole(),Qt::red);
    error_message->setPalette(palette);

    this->setWindowTitle("Sign in");
    this->setMinimumSize(200,300);

    QFont f;
    f.setPointSize(15);

    back_button = new QPushButton();

    back_button->setIcon(QIcon(":/thumbnails/back_button.png"));
    back_button->setIconSize(QSize(30, 30));
    back_button->setFixedSize(30,30);

    username = new QLabel("username/email");
    username->setFont(f);
    username->setStyleSheet(QString("color: %1").arg(col.name()));

    password = new QLabel("password");
    password->setFont(f);
    password->setStyleSheet(QString("color: %1").arg(col.name()));

    username_box = new QLineEdit;
    username_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    pass_box = new QLineEdit;
    pass_box->setEchoMode(QLineEdit::Password);
    pass_box->setStyleSheet("QLineEdit {font-size:20px; border: 3px solid white; border-radius:5px; color:white;}");

    log_in = new QPushButton("Log in");
    log_in->setMinimumSize(100,20);
    log_in->setStyleSheet(QString("QPushButton {font-size: 20px; background-color: %1 ;}").arg(col.name()));
    hbox = new QHBoxLayout();

    //adding widgets to a grid and Hbox
    QGridLayout * grid = new QGridLayout;
    grid->addWidget(username,0,0);
    grid->addWidget(username_box,0,1);
    grid->addItem(new QSpacerItem(50, 10), 1, 0,1,2);
    grid->addWidget(password,2,0);
    grid->addWidget(pass_box,2,1);
    grid->addItem(new QSpacerItem(50, 10), 3, 0,2,2);

    hbox->addWidget(log_in);

    grid->addItem(hbox,6,0,1,3,Qt::AlignHCenter);

    //adding the grid and Hbox and widgets to a Vbox which is then displayed
    layout = new QVBoxLayout();
    layout->addItem(grid);
    layout->addWidget(error_message);
    layout->addWidget(back_button,Qt::AlignLeft | Qt::AlignBottom);


    this->setLayout(layout);

    //signal slot connections
    QObject::connect(back_button,SIGNAL(clicked()),this,SLOT(ClickReturn()));
    QObject::connect(log_in,SIGNAL(clicked()),this,SLOT(VerifyCredentials()));
}

void SignInWidget::VerifyCredentials(){//passes the input to attemptSignIn.
    QString user = this->username_box->text();
    QString pass = this->pass_box->text();

    Accounts * acc = new Accounts(user,pass);
    QString result = acc->AttemptSignIn();
    if (result!="success")
        error_message->setText(result);//failed verification
    else{
        this->close();
        MainMenuWidget *menu = new MainMenuWidget(acc);//verification succes, transitions to mainmenu
    }
}

void SignInWidget:: ClickReturn()//returns the user to the welcome screen if the return button is pushed
{
    this->close();
    WelcomeWidget * scene = new WelcomeWidget();
    scene->setMinimumSize(300,300);
    scene->show();
}
