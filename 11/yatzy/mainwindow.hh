#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "yatzygame.hh"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    // The constructor.
    MainWindow(YatzyGame* game, QWidget* parent = nullptr);

    // The destructor.
    ~MainWindow();

public slots:

    // Called to roll all unkept die.
    void roll();

    // Called for different scoring types.
    void scoreOnes();
    void scoreOnePair();
    void scoreTwoPairs();
    void scoreSmallStraight();
    void scoreYatzy();

    // Called to reset the game.
    void reset();

private:

    // Updates the shown dice with the given rolls.
    void updateDice(std::vector<unsigned int> const& rolls);

    // Updates the shown controls and labels.
    void updateControls();

    // Sets the widget layout.
    void setupLayout();

    // The yatzy game logic.
    YatzyGame* game_;

    // The shown die rolls.
    std::vector<QLabel*> dice_;

    // Button for activating a roll on all unkept die.
    QPushButton rollButton_;

    // Label for showing remaining number of rolls.
    QLabel rollCountLabel_;

    // Buttons for keeping die.
    std::vector<QPushButton*> keepButtons_;

    // Label for score.
    QLabel onesScoreLabel_;

    // Button for activating score count for ones.
    QPushButton scoreOnesButton_;

    // Label for score.
    QLabel onePairScoreLabel_;

    // Button for activating score count for one pair.
    QPushButton scoreOnePairButton_;

    // Label for score.
    QLabel twoPairsScoreLabel_;

    // Button for activating score count for two pairs.
    QPushButton scoreTwoPairsButton_;

    // Label for score.
    QLabel smallStraightScoreLabel_;

    // Button for activating score count for small straight.
    QPushButton scoreSmallStraightButton_;

    // Label for score.
    QLabel yatzyScoreLabel_;

    // Button for activating score count for two pairs.
    QPushButton scoreYatzyButton_;

    // Label for total score.
    QLabel totalScoreLabel_;

    // Button for resetting the game.
    QPushButton resetButton_;

    // Button for ending the game.
    QPushButton quitButton_;

};

#endif // MAINWINDOW_H
