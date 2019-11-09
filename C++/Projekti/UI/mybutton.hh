#ifndef MYBUTTON_HH
#define MYBUTTON_HH
#include <QPushButton>
#include <QMouseEvent>
#include <QMouseEvent>

namespace Student{

class MyButton : public QPushButton
{
    Q_OBJECT

public:

    explicit MyButton(const QString & text, QWidget * parent = nullptr, int index = 0);
    virtual ~MyButton();

signals:

    /**
     * @brief movePawn Tells mainwindow to move pawn.
     * @param pawnIndex Index of the pawn.
     */
    void movePawn(int pawnIndex);

private:

    int index_;

protected:

    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);
};
}
#endif // MYBUTTON_HH
