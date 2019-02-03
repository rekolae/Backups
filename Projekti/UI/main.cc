#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "mainwindow.hh"

#include <memory>
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Student::MainWindow w;

    w.setStyleSheet("QMainWindow {background: gray;}");
    w.move(100,100);
    w.show();

    return QApplication::exec();
}
