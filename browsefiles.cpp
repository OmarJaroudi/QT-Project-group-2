#include "browsefiles.h"

BrowseFiles::BrowseFiles(QWidget *parent) : QWidget(parent)
{
    Disp= new QWidget();
    Browse= new QFileDialog();
    layout= new QVBoxLayout();
    Browse->setNameFilter(tr ("JPEG/PNG (*.jpg *.jpeg *.png)"));
    layout->addWidget(Browse);
    Disp->setLayout(layout);

    QObject::connect(Browse,SIGNAL(fileSelected(QString)),this,SLOT(ChooseFile()));

}

void BrowseFiles::ChooseFile()
{
    directory = Browse->selectedFiles()[0];
    //QString destinationPath= "/home/eece435l/Desktop/IUwo6l_Q-copy.jpg";
    //QFile::copy(Browse->selectedFiles()[0],destinationPath);
    Disp->close();

}

