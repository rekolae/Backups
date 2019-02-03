#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include <QLineEdit>
#include <QLayout>
#include <vector>
#include <iostream>

namespace Ui {
class Dialog;
}


namespace Student{
class Dialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief GameOverdDialog Constructor.
     * @param parent Parent widget.
     */
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:

    /**
     * @brief configParameters Sends configuration settings to mainwindow.
     * @param configSuccess_ True if config was a success, false if not.
     * @param playerNames Vector holding players' names.
     */
    void configParameters(bool configSuccess_,
                          std::vector<std::string> playerNames);

private slots:

    /**
     * @brief on_Ok_clicked Handels the clicking of 'OK'-button.
     */
    void on_Ok_clicked();

    /**
     * @brief on_Close_clicked Handels the clicking of 'Close'-button.
     */
    void on_Close_clicked();

    /**
     * @brief on_spinBox_valueChanged Hides and shows player name text fields.
     * @param spinBoxValue Value of the spinbox.
     */
    void on_spinBox_valueChanged(int spinBoxValue);

    /**
     * @brief reject Handels closing the window via Esc-key.
     */
    void reject();

private:
    /**
     * @brief closeEvent Handels the closing of the window through e.g. ALT+F4.
     */
    void closeEvent(QCloseEvent *);

    /**
     * @brief playerNamesToVector Takes player names and adds them to a vector.
     * @return Vector containing player names.
     */
    std::vector<std::string>playerNamesToVector();

    Ui::Dialog* ui;

    std::vector<QLineEdit*>playerNameFields_;
    std::vector<std::string>playerNames_;

    bool configSuccess_;
};
}

#endif // DIALOG_HH
