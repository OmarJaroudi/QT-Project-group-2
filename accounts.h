#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "simplecrypt.h"

class Accounts
{
public:
    Accounts(QString username,QString password, QString confirmPass, QString DOB, QString email, QString fName,QString lName,QString imgPath);
    Accounts(QString username,QString password);
    QString attemptSignUp();
    QString attemptSignIn();
    QString getDOB();
    QString getImgPath();
    QString getUsername();
    QString getFName();

private:bool ValidateEmail(QString email);
     QString EncryptPass(QString plaintext);
     QString DecryptPass(QString ciphertext);
     long key;
     QString username;
     QString password;
     QString confirmPass;
     QString email;
     QString DOB;
     QString fName;
     QString lName;
     QString imgPath;

};

#endif // ACCOUNTS_H
