#include "dialog.hh"
#include "ui_dialog.h"

const unsigned int MAX_PLAYER_AMOUNT = 4;

namespace Student{

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    configSuccess_ = false;

    ui->setupUi(this);

    //Hides button from title bar
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    ui->player1Name->setText("Player 1");
    ui->player2Name->setText("Player 2");
    ui->player3Name->setText("Player 3");
    ui->player3Name->hide();
    ui->player3NameLabel->hide();
    ui->player4Name->setText("Player 4");
    ui->player4Name->hide();
    ui->player4NameLabel->hide();

    playerNameFields_.push_back(ui->player1Name);
    playerNameFields_.push_back(ui->player2Name);
    playerNameFields_.push_back(ui->player3Name);
    playerNameFields_.push_back(ui->player4Name);
}


void Dialog::on_Ok_clicked()
{
    configSuccess_ = true;
    playerNames_ = playerNamesToVector();
    emit configParameters(configSuccess_, playerNames_);
}


void Dialog::on_Close_clicked()
{
    configSuccess_ = false;
    emit configParameters(configSuccess_, playerNames_);
}


Dialog::~Dialog()
{
    delete ui;
}


std::vector<std::string>Dialog::playerNamesToVector()
{
    for (unsigned int i = 0; i < MAX_PLAYER_AMOUNT; i++){
        if (!playerNameFields_.at(i)->isHidden()){
            QString qsname = playerNameFields_.at(i)->text();
            std::string name = qsname.toStdString();
            playerNames_.push_back(name);
        }
    }

    return playerNames_;
}


void Dialog::on_spinBox_valueChanged(int spinBoxValue)
{
    if (spinBoxValue == 2){
        playerNameFields_.at(2)->hide();
        ui->player3NameLabel->hide();
        playerNameFields_.at(3)->hide();
        ui->player4NameLabel->hide();
    }

    else if (spinBoxValue == 3){
        playerNameFields_.at(2)->show();
        ui->player3NameLabel->show();
        playerNameFields_.at(3)->hide();
        ui->player4NameLabel->hide();
    }

    else {
        playerNameFields_.at(2)->show();
        ui->player3NameLabel->show();
        playerNameFields_.at(3)->show();
        ui->player4NameLabel->show();
    }
}


void Dialog::reject()
{
    if (configSuccess_ == false) {
        emit configParameters(configSuccess_, playerNames_);
    }
}


void Dialog::closeEvent(QCloseEvent *)
{
    if (configSuccess_ == false) {
        emit configParameters(configSuccess_, playerNames_);
    }
}

}
