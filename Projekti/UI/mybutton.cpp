#include "mybutton.hh"


namespace Student{

MyButton::MyButton(const QString &text, QWidget *parent, int index):
    QPushButton(text, parent),index_(index)
{
}


MyButton::~MyButton()= default;


void MyButton::mousePressEvent(QMouseEvent *event)
{
    emit movePawn(index_);
    event->accept();
};
}
