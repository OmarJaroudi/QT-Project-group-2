#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>
#include "browsefiles.h"
#include "accounts.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDateEdit>

class SignUpWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief SignUpWidget constructor
     * @param parent
     */
    explicit SignUpWidget(QWidget *parent = nullptr);
    BrowseFiles * browser;
    QLabel * img_location;
    QLabel * error_message;
    QLabel * prompt;
    QLabel * first_name;
    QLabel * last_name;
    QLabel * username;
    QLabel * email;
    QLabel * password;
    QLabel * confirm_password;
    QLabel * birth_date;
    QLabel * profile_pic;
    QPushButton * create;
    QPushButton * back_button;
    QLineEdit * first_name_box;
    QLineEdit * last_name_box;
    QLineEdit * username_box;
    QLineEdit * email_box;
    QLineEdit * password_box;
    QLineEdit * confirm_password_box;
    QGridLayout * grid;
    QDateEdit * date;
    QFileDialog * browse;
    QPushButton * choose_pic;
    Accounts *account;
public slots:
    /**
     * @brief BrowseForImage: slot executes when select picture button is pressed
     *
     * Opens a window for the user to select a profile picture
     */
    void BrowseForImage();
    /**
     * @brief VerifyCredentials: slot executes when the return button is pushed
     *
     * returns the user to the welcome screen.
     */
    void ClickReturn();
    /**
     * @brief VerifyCredentials: slot executes when the sign up button is pushed
     *
     * passes the info entered into an instance of account. Attempts sign up.
     */
    void CreateAccount();


signals:

};

#endif // SIGNUPCLASS_H
