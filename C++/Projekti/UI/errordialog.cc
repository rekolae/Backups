#include "errordialog.hh"
#include "ui_errordialog.h"

namespace Student{

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);

    //Hides button from title bar
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}


ErrorDialog::~ErrorDialog()
{
    delete ui;
}


void ErrorDialog::on_okButton_clicked()
{
    emit exitGame();
}


void ErrorDialog::reject()
{
    emit exitGame();
}

void ErrorDialog::errorMode(int mode)
{
    if (mode == 0){
        ui->instructionsErrorHeader->hide();
        ui->instructionsErrorLabel->hide();
    }

    else {
        ui->initErrorHeader1->hide();
        ui->initErrorHeader2->hide();
        ui->initErrorLabel->hide();
    }
}


void ErrorDialog::closeEvent(QCloseEvent *)
{
    emit exitGame();
}

}
