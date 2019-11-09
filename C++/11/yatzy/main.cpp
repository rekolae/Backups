#include "mainwindow.hh"
#include "yatzygame.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YatzyGame game(5);
    MainWindow w(&game);
    w.show();

    return a.exec();
}
