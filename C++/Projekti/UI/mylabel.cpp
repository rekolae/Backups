#include "mylabel.h"


namespace Student{

myLabel::myLabel( QWidget *parent): QLabel(parent)
{

}


void myLabel::addText(std::string text)
{
    this->clear();
    for(unsigned int i=0; i < textRows_.size()-1;++i){
        textRows_.at(i) = textRows_.at(i+1);
    }
    int lastRow = 6;
    textRows_.at(lastRow) =  std::move(text);
    std::string text2;

    for(unsigned int i=0; i < textRows_.size();++i){
        if(i == textRows_.size()-1){
             text2 += ">"+ textRows_.at(i);
        }
        else{
            text2 += "  "+ textRows_.at(i) + "\n";
        }
    }
    this->setText(QString::fromStdString(text2));
};
}
