#ifndef HELPDIALOG_HH
#define HELPDIALOG_HH

#include "ioexception.hh"

#include <QDialog>
#include <QString>
#include <QTextStream>
#include <QFile>



namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief GameOverdDialog Constructor.
     * @param parent Parent widget.
     */
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

    /**
     * @brief readHelpFile Reads help file and adds the text to help dialog.
     */
    void readHelpFile();

private slots:

    /**
     * @brief on_okButton_clicked Handels the clicking of the 'ok'-button.
     */
    void on_okButton_clicked();

    /**
     * @brief reject Handels closing the window via Esc-key.
     */
    void reject();

private:

    Ui::HelpDialog *ui;

    /**
     * @brief closeEvent Handels the closing of the window.
     */
    void closeEvent(QCloseEvent *);

};

#endif // HELPDIALOG_HH
