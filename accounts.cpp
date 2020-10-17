#include "accounts.h"
#include <QDebug>

Accounts::Accounts(QString username,QString password, QString confirmPass, QString DOB, QString email, QString fName,QString lName,QString imgPath)
{
    key = Q_UINT64_C(0x0c2ad4a4acb9f023);//encryption key
    this->username = username;
    this->password = password;
    this->confirm_pass = confirmPass;
    this ->email = email;
    this->dob = DOB;
    this->f_name = fName;
    this->l_name = lName;
    this->img_path = imgPath;

}
Accounts::Accounts(QString username,QString password)//basic constructor passed for a sign in
{
    key = Q_UINT64_C(0x0c2ad4a4acb9f023);
    this->username = username;
    this->password = password;

}
QString Accounts::AttemptSignIn(){//
    if (username==NULL || password == NULL){
        return("username or password field is empty!");
    }
    else {
        bool found = false;
        bool verified = false;
        QString found_username = "";
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
                        found_username = tempLine[0];
                        verified = true;
                        this->username = tempLine[0];
                        this->email = tempLine[2];
                        this->f_name = tempLine[3];
                        this->l_name = tempLine[4];
                        this->dob = tempLine[5];
                        this->img_path = tempLine[6];
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

QString Accounts::AttemptSignUp(){
QRegExp re("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])");
    if(username==NULL||
            password==NULL||
            confirm_pass == NULL ||
            f_name == NULL ||
            l_name == NULL ||
            email == NULL||
            dob == NULL) {
        return("Error empty field(s)!");//checks for empty fields
    }

    if(username.contains(" ")||
            password.contains(" ")||
            confirm_pass.contains(" ") ||
            f_name.contains(" ") ||
            l_name.contains(" ") ||
            email.contains(" ")) {
        return("Fields cannot contain whitespace!");//checks for the presence of any whitespace. Whitespaces are used to sperate info in the txt file.
    }

    else if (!ValidateEmail(email)){//validate possible email
        return("Invalid email address!");
    }
    else if (password!=confirm_pass){//pass!=confirm pass
        return("Passwords don't match!");
    }
    else if(password.length()<8){//password too short
        return("Password must be longer than 8 characters!");
    }
    else if (re.indexIn(password)==-1){//password does not meet other requirements
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
        if (img_path==NULL)//no picture selected
            return ("Please select a profile picture!");

        //add image directory into the info string
        QFileInfo imgInfo(img_path);
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
        bool status = QFile::copy(img_path, newPath);
        if (status == false)
            return ("Error adding profile picture!");
        QString data = (username + " " +
                    EncryptPass(password) + " " +
                    email + " " +
                    f_name + " " +
                    l_name + " " +
                    dob + " " +
                    newPath);
        this->img_path = newPath;
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
QString  Accounts::GetDOB(){
    return (*(new QString(dob)));
}

QString  Accounts::GetUsername(){
    return (*(new QString(username)));
}
QString  Accounts::GetFName(){
    return (*(new QString(f_name)));
}
QString  Accounts::GetImgPath(){
    return (*(new QString(img_path)));
}
