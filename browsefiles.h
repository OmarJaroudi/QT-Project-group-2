#ifndef BROWSEFILES_H
#define BROWSEFILES_H

#include <QWidget>
#include <QtWidgets>

class BrowseFiles : public QWidget
{
    Q_OBJECT
public:
    explicit BrowseFiles(QWidget *parent = nullptr);
    QString directory;
    QWidget * disp;
    QFileDialog * browse;
    QVBoxLayout * layout;
    QString * dir;
public slots:
    void ChooseFile();

signals:


};


#endif // BROWSEFILES_H
