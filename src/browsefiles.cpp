#include "browsefiles.h"

BrowseFiles::BrowseFiles(QWidget *parent) : QWidget(parent)
{
    disp= new QWidget();
    browse= new QFileDialog();
    layout= new QVBoxLayout();
    browse->setNameFilter(tr ("JPEG/PNG (*.jpg *.jpeg *.png)"));//ensures the user selects an image
    layout->addWidget(browse);
    disp->setLayout(layout);

    QObject::connect(browse,SIGNAL(fileSelected(QString)),this,SLOT(ChooseFile()));

}

void BrowseFiles::ChooseFile()//closes the pop up after an image is selected
{
    directory = browse->selectedFiles()[0];
    //QString destinationPath= "/home/eece435l/Desktop/IUwo6l_Q-copy.jpg";
    //QFile::copy(Browse->selectedFiles()[0],destinationPath);
    disp->close();

}

