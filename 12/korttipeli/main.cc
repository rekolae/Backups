#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication blackjack(argc, argv);
    MainWindow game_window;
    game_window.setFixedSize(1000, 1000);
    game_window.show();

    return blackjack.exec();
}
