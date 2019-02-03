#include "gameoverddialog.hh"
#include "ui_gameoverddialog.h"


namespace Student{

GameOverdDialog::GameOverdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverdDialog)
{
    ui->setupUi(this);

    //Hides buttons from title bar
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    ui->player1->hide();
    ui->player1Points->hide();
    ui->player2->hide();
    ui->player2Points->hide();
    ui->player3->hide();
    ui->player3Points->hide();
    ui->player4->hide();
    ui->player4Points->hide();
}


GameOverdDialog::~GameOverdDialog()
{
    delete ui;
}


void GameOverdDialog::displayData(std::map<int, std::string> results,
                                  std::vector<int> points)
{    
    unsigned int playerAmount = results.size();

    //Sorts the contents from biggest to smallest.
    std::sort(points.begin(), points.end(), std::greater<>());

    QString pointsQstring;
    QString nameQstring;

    if (playerAmount >= 2){

        ui->player1->show();
        ui->player1Points->show();
        ui->player2->show();
        ui->player2Points->show();

        pointsQstring = QString::number(points.at(0));
        nameQstring = QString::fromStdString(results.at(points.at(0)));
        ui->player1->setText(nameQstring);
        ui->player1Points->setText(pointsQstring);

        pointsQstring = QString::number(points.at(1));
        nameQstring = QString::fromStdString(results.at(points.at(1)));
        ui->player2->setText(nameQstring);
        ui->player2Points->setText(pointsQstring);
    }

    else if (playerAmount >= 3){

        ui->player3->show();
        ui->player3Points->show();

        pointsQstring = QString::number(points.at(2));
        nameQstring = QString::fromStdString(results.at(points.at(2)));
        ui->player3->setText(nameQstring);
        ui->player3Points->setText(pointsQstring);
    }

    else {

        ui->player4->show();
        ui->player4Points->show();

        pointsQstring = QString::number(points.at(3));
        nameQstring = QString::fromStdString(results.at(points.at(3)));
        ui->player4->setText(nameQstring);
        ui->player4Points->setText(pointsQstring);
    }
}


void GameOverdDialog::closeEvent(QCloseEvent *)
{
    emit gameOver();
}


void GameOverdDialog::on_okButton_clicked()
{
    emit gameOver();
}


void GameOverdDialog::reject()
{
    emit gameOver();
}

}
