#include "helpdialog.hh"
#include "ui_helpdialog.h"


HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{

    ui->setupUi(this);

    //Hides buttons from title bar
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}


HelpDialog::~HelpDialog()
{
    delete ui;
}


void HelpDialog::on_okButton_clicked()
{
    this->close();
}


void HelpDialog::reject()
{
    this->close();
}


void HelpDialog::closeEvent(QCloseEvent *)
{
    this->close();
}

void HelpDialog::readHelpFile()
{
    QString fullText = "";
    QFile file(QString::fromStdString(":/textFiles/Instructions.txt"));

    //Tries to open the file and throws an error if it can't be opened.
    if (!file.open(QFile::ReadOnly)){
        throw Common::IoException();
    }

    else {
        QTextStream in(&file);
        while (!in.atEnd()){
            QString line = in.readLine();
            fullText += line + "\n";
        }

        ui->textBrowser->setText(fullText);
        file.close();
    }
}
