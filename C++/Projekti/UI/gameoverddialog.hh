#ifndef GAMEOVERDDIALOG_HH
#define GAMEOVERDDIALOG_HH

#include <QDialog>
#include <QString>
#include <vector>
#include <string>
#include <map>

namespace Ui {
class GameOverdDialog;
}


namespace Student{
class GameOverdDialog : public QDialog
{
    Q_OBJECT

signals:
    void gameOver();

public:
    /**
     * @brief GameOverdDialog Constructor.
     * @param parent Parent widget.
     */
    explicit GameOverdDialog(QWidget *parent = nullptr);
    ~GameOverdDialog();

    /**
     * @brief displayData Handels showing game data in the window.
     * @param results Contains player points with corresponding names.
     * @param points List of points.
     */
    void displayData(std::map<int, std::string> results,
                     std::vector<int> points);

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
    Ui::GameOverdDialog *ui;

    /**
     * @brief closeEvent Handels the closing of the window.
     */
    void closeEvent(QCloseEvent *);
};
}

#endif // GAMEOVERDDIALOG_HH
