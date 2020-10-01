#include "accounts.h"
#include <QDebug>

Accounts::Accounts(QString username,QString password, QString confirmPass, QString DOB, QString email, QString fName,QString lName,QString imgPath)
{
    key = Q_UINT64_C(0x0c2ad4a4acb9f023);//encryption key
    this->username = username;
    this->password = password;
    this->confirmPass = confirmPass;
    this ->email = email;
    this->DOB = DOB;
    this->fName = fName;
    this->lName = lName;
    this->imgPath = imgPath;

}
Accounts::Accounts(QString username,QString password)//basic constructor passed for a sign in
{
    key = Q_UINT64_C(0x0c2ad4a4acb9f023);
    this->username = username;
    this->password = password;

}
QString Accounts::attemptSignIn(){//
    if (username==NULL || password == NULL){
        return("username or password field is empty!");
    }
    else {
        bool found = false;
        bool verified = false;
        QString foundUsername = "";
        //access the txt file where the info is stored
        QString path = QDir::currentPath();
        path.append("/userData/data.txt");
        QFile inputFile(path);
        if (inputFile.size()!=0){
        inputFile.open(QIODevice::ReadOnly);//configure to read and write
        QTextStream stream(&inputFile);
            QString line = stream.readLine();
            while (!line.isNull()) { //extract info from txt file to verify
                QStringList tempLine = line.split(" ");
                if (tempLine[0]==username || tempLine[2]==username){//check username or email exist
                    found = true;
                    if (DecryptPass(tempLine[1])==password){//check password match
                        //set the rest of the Account parameters
                        foundUsername = tempLine[0];
                        verified = true;
                        this->username = tempLine[0];
                        this->email = tempLine[2];
                        this->fName = tempLine[3];
                        this->lName = tempLine[4];
                        this->DOB = tempLine[5];
                        this->imgPath = tempLine[6];
                        break;
                    }
                }
                line = stream.readLine();
            }
        }

        //return success or an error message
        if (verified==true && found==true)
            return("success");
        else if (found == true)
            return("Password is incorrect!");
        else
            return("Username or email doesn't exist!");
    }
}

QString Accounts::attemptSignUp(){
    QRegExp re("^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])");

    if(username==NULL||
            password==NULL||
            confirmPass == NULL ||
            fName == NULL ||
            lName == NULL ||
            email == NULL||
            DOB == NULL) {
        return("Error empty field(s)!");//checks for empty fields
    }

    if(username.contains(" ")||
            password.contains(" ")||
            confirmPass.contains(" ") ||
            fName.contains(" ") ||
            lName.contains(" ") ||
            email.contains(" ")) {
        return("Fields cannot contain whitespace!");//checks for the presence of any whitespace. Whitespaces are used to sperate info in the txt file.
    }

    else if (!ValidateEmail(email)){//validate possible email
        return("Invalid email address!");
    }
    else if (password!=confirmPass){//pass!=confirm pass
        return("Passwords don't match!");
    }
    else if(password.length()<8){//password too short
        return("Password must be longer than 8 characters!");
    }
    else if (re.exactMatch(password)){//password does not meet other requirements
        return("Password must contain 1 uppercase char, \n1 lowecase char, and 1 number!");
    }
    else {
        //set up to write to the txt file
        QString path = QDir::currentPath();
        path.append("/userData");
        if (!QDir(path).exists())
            QDir().mkdir(path);
        path.append("/data.txt");

        QFile inputFile(path);
        inputFile.open(QIODevice::ReadWrite);
        QTextStream stream(&inputFile);
        if (inputFile.size()!=0){
            QString line = stream.readLine();
            while (!line.isNull()) {
                QStringList tempLine = line.split(" ");
                if (tempLine[0]==username)//check for duplicate username
                    return("Username already taken!");
                else if (tempLine[2]==email)//check for duplicate email
                    return("Email already registered!");
                line = stream.readLine();
            }
        }
        if (imgPath==NULL)//no picture selected
            return ("Please select a profile picture!");

        //add image directory into the info string
        QFileInfo imgInfo(imgPath);
        QString newPath = QDir::currentPath();
        newPath.append("/userDP");
        if (!QDir(newPath).exists())
            QDir().mkdir(newPath);
        newPath.append("/" + username+ "." + imgInfo.suffix());
        qDebug()<<newPath;
        if (QFile::exists(newPath))
        {
            QFile::remove(newPath);
        }

        //write all the account info into the txt file
        bool status = QFile::copy(imgPath, newPath);
        if (status == false)
            return ("Error adding profile picture!");
        QString data = (username + " " +
                    EncryptPass(password) + " " +
                    email + " " +
                    fName + " " +
                    lName + " " +
                    DOB + " " +
                    newPath);
        this->imgPath = newPath;
        stream<<data<<endl;
        inputFile.close();
        return "success";
    }

}
bool Accounts::ValidateEmail(QString email){//check if the string entered is really an email (doesnt have to be active)
    email = email.toLower();
    QRegExp re("([a-z]+)([_.a-z0-9]*)([a-z0-9]+)(@)([a-z]+)([.a-z]+)([a-z]+)");
    if (re.exactMatch(email))
        return true;

    return false;
}
//encyrpt and decrypt
QString Accounts::EncryptPass(QString plaintext){
   SimpleCrypt crypto(this->key);
    return (crypto.encryptToString(plaintext));
}

QString Accounts::DecryptPass(QString ciphertext){
    SimpleCrypt crypto(this->key);
    return(crypto.decryptToString(ciphertext));
}

//setters and getters
QString  Accounts::getDOB(){
    return (*(new QString(DOB)));
}

QString  Accounts::getUsername(){
    return (*(new QString(username)));
}
QString  Accounts::getFName(){
    return (*(new QString(fName)));
}
QString  Accounts::getImgPath(){
    return (*(new QString(imgPath)));
}
