#ifndef ERRORDIALOG_HH
#define ERRORDIALOG_HH

#include <QDialog>
#include <vector>
#include <iostream>

namespace Ui {
class ErrorDialog;
}

namespace Student{


class ErrorDialog : public QDialog
{
    Q_OBJECT

signals:

    /**
     * @brief exitProgram Sends signal to mainwindow to exit program.
     */
    void exitGame();

public:

    /**
     * @brief GameOverdDialog Constructor.
     * @param parent Parent widget.
     */
    explicit ErrorDialog(QWidget *parent = nullptr);
    ~ErrorDialog();

    /**
     * @brief errorMode Sets the appropriate message in the error dialog.
     * @param mode Number corresponding to error type.
     */
    void errorMode(int mode);

private slots:

    /**
     * @brief on_okButton_clicked Handels the clicking of 'ok'-button.
     */
    void on_okButton_clicked();

    /**
     * @brief reject Handels closing the window via Esc-key.
     */
    void reject();

private:

    Ui::ErrorDialog *ui;

    /**
     * @brief closeEvent Handels the closing of the window through e.g. ALT+F4.
     */
    void closeEvent(QCloseEvent *);

};
}
#endif // ERRORDIALOG_HH
