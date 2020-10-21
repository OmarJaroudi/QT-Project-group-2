#ifndef VIRUSOBJECT_H
#define VIRUSOBJECT_H
#include "clickablelabel.h"

class VirusObject : public ClickableLabel
{
    Q_OBJECT
public:
    enum Color {GREEN,BLUE,YELLOW};
    QString getColor();
    int getScore();
    int getSize();
    VirusObject();
    VirusObject(VirusObject::Color c,int size);

private:
    Color color;
    int score;
    int size;

};

#endif // VIRUSOBJECT_H
