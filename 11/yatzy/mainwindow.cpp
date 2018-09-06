#include "mainwindow.hh"
#include "yatzygame.hh"
#include "yatzyrules.hh"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QGroupBox>

MainWindow::MainWindow(YatzyGame* game, QWidget *parent): QWidget(parent),
    game_(game),
    dice_(),
    rollButton_("Roll", this),
    rollCountLabel_(this),
    keepButtons_(),

    onesScoreLabel_(this),
    scoreOnesButton_("Score Ones", this),

    onePairScoreLabel_(this),
    scoreOnePairButton_("Score One Pair", this),

    twoPairsScoreLabel_(this),
    scoreTwoPairsButton_("Score Two Pairs", this),

    smallStraightScoreLabel_(this),
    scoreSmallStraightButton_("Score Small Straight", this),

    yatzyScoreLabel_(this),
    scoreYatzyButton_("Score Yatzy", this),

    totalScoreLabel_(this),
    resetButton_("Reset", this),
    quitButton_("Quit", this)
{
    setupLayout();

    // When roll button is pressed, roll all dice.
    connect(&rollButton_, SIGNAL(clicked(bool)), this, SLOT(roll()));

    connect(&scoreOnesButton_, SIGNAL(clicked(bool)), this, SLOT(scoreOnes()));
    connect(&scoreOnePairButton_, SIGNAL(clicked(bool)), this, SLOT(scoreOnePair()));
    connect(&scoreTwoPairsButton_, SIGNAL(clicked(bool)), this, SLOT(scoreTwoPairs()));
    connect(&scoreSmallStraightButton_, SIGNAL(clicked(bool)), this, SLOT(scoreSmallStraight()));
    connect(&scoreYatzyButton_, SIGNAL(clicked(bool)), this, SLOT(scoreYatzy()));

    connect(&resetButton_, SIGNAL(clicked(bool)), this, SLOT(reset()));

    // When quit button is pressed, the window is closed and application shuts down.
    connect(&quitButton_, SIGNAL(clicked(bool)), this, SLOT(close()));

    updateControls();
}

MainWindow::~MainWindow()
{

}

void MainWindow::roll()
{
    for (int dieNumber = 0; dieNumber < YatzyRules::NUMBER_OF_DICE; dieNumber++)
    {
        bool keepDie = keepButtons_.at(dieNumber)->isChecked();
        if (keepDie)
        {
            game_->keepRoll(dieNumber);
        }
    }

    std::vector<unsigned int> newRolls = game_->roll();
    updateDice(newRolls);

    updateControls();
}

void MainWindow::scoreOnes()
{
    unsigned int score = game_->scoreOnes();
    onesScoreLabel_.setText(QString::number(score));

    updateControls();
}

void MainWindow::scoreOnePair()
{        
    unsigned int score = game_->scoreOnePair();
    onePairScoreLabel_.setText(QString::number(score));

    updateControls();
}

void MainWindow::scoreTwoPairs()
{
    unsigned int score = game_->scoreTwoPairs();
    twoPairsScoreLabel_.setText(QString::number(score));

    updateControls();
}

void MainWindow::scoreSmallStraight()
{
    unsigned int score = game_->scoreSmallStraight();
    smallStraightScoreLabel_.setText(QString::number(score));

    updateControls();
}

void MainWindow::scoreYatzy()
{
    unsigned int score = game_->scoreYatzy();
    yatzyScoreLabel_.setText(QString::number(score));

    updateControls();
}

void MainWindow::reset()
{
    onesScoreLabel_.clear();
    onePairScoreLabel_.clear();

    game_->reset();
    updateControls();
}

void MainWindow::updateDice(std::vector<unsigned int> const& rolls)
{
    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        QPixmap dieImage(":/dice/" + QString::number(rolls.at(i)) + ".gif");
        dice_.at(i)->setPixmap(dieImage);
    }
}

void MainWindow::updateControls()
{
    unsigned int rollsLeft = game_->getNumberOfRollsLeft();
    for (int dieNumber = 0; dieNumber < YatzyRules::NUMBER_OF_DICE; dieNumber++)
    {
        keepButtons_.at(dieNumber)->setEnabled(game_->canKeep(dieNumber));

        // At the start of a round, all keep buttons are reset.
        if (rollsLeft == YatzyRules::ROLLS_PER_TURN)
        {
            keepButtons_.at(dieNumber)->setChecked(false);
        }
    }

    rollButton_.setEnabled(rollsLeft > 0);

    scoreOnesButton_.setEnabled(game_->canScore(YatzyRules::ONES));
    scoreOnePairButton_.setEnabled(game_->canScore(YatzyRules::ONE_PAIR));
    scoreTwoPairsButton_.setEnabled(game_->canScore(YatzyRules::TWO_PAIRS));
    scoreSmallStraightButton_.setEnabled(game_->canScore(YatzyRules::SMALL_STRAIGHT));
    scoreYatzyButton_.setEnabled(game_->canScore(YatzyRules::YATZY));

    rollCountLabel_.setText(QString("Rolls left: %1").arg(game_->getNumberOfRollsLeft()));
    totalScoreLabel_.setText(QString::number(game_->getTotalScore()));
}

void MainWindow::setupLayout()
{
    QGridLayout* layout = new QGridLayout();

    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        QLabel* die = new QLabel(this);
        QPixmap dieImage(":/dice/1.gif");
        die->setPixmap(dieImage);
        dice_.push_back(die);

        QPushButton* keepButton = new QPushButton("Keep", this);
        keepButton->setObjectName(QString("keepButton") + QString::number(i));
        keepButton->setCheckable(true);
        keepButton->setDisabled(true);
        keepButtons_.push_back(keepButton);

        layout->addWidget(die, 0, i, 1, 1);
        layout->addWidget(keepButton, 1, i, 1, 1);
    }

    // Add names for the widgets to allow automated testing to access them.
    rollButton_.setObjectName("rollButton");
   
    scoreOnesButton_.setObjectName("scoreOnesButton");
    scoreOnePairButton_.setObjectName("scoreOnePairButton");
    scoreTwoPairsButton_.setObjectName("scoreTwoPairsButton");
    scoreSmallStraightButton_.setObjectName("scoreSmallStraightButton");
    scoreYatzyButton_.setObjectName("scoreYatzyButton");

    onesScoreLabel_.setObjectName("onesScoreLabel");
    onePairScoreLabel_.setObjectName("onePairScoreLabel");
    twoPairsScoreLabel_.setObjectName("twoPairsScoreLabel");
    smallStraightScoreLabel_.setObjectName("smallStraightScoreLabel");
    yatzyScoreLabel_.setObjectName("yatzyScoreLabel");

    totalScoreLabel_.setObjectName("totalScoreLabel");

    // Layout the widgets in the window.
    layout->addWidget(&rollButton_, 5, 0, 1, YatzyRules::NUMBER_OF_DICE);
    layout->addWidget(&rollCountLabel_, 6, 0, 1, 1);

    QGroupBox* scoreTable = new QGroupBox("Score card", this);
    QGridLayout* scoreLayout = new QGridLayout(scoreTable);

    scoreLayout->addWidget(new QLabel("Ones:", this), 0, 0, 1, 1);
    scoreLayout->addWidget(&onesScoreLabel_, 0, 1, 1, 1);
    scoreLayout->addWidget(&scoreOnesButton_, 0, 2, 1, 1);

    scoreLayout->addWidget(new QLabel("One pair:", this), 1, 0, 1, 1);
    scoreLayout->addWidget(&onePairScoreLabel_, 1, 1, 1, 1);
    scoreLayout->addWidget(&scoreOnePairButton_, 1, 2, 1, 1);

    scoreLayout->addWidget(new QLabel("Two pairs:", this), 2, 0, 1, 1);
    scoreLayout->addWidget(&twoPairsScoreLabel_, 2, 1, 1, 1);
    scoreLayout->addWidget(&scoreTwoPairsButton_, 2, 2, 1, 1);

    scoreLayout->addWidget(new QLabel("Small straight:", this), 3, 0, 1, 1);
    scoreLayout->addWidget(&smallStraightScoreLabel_, 3, 1, 1, 1);
    scoreLayout->addWidget(&scoreSmallStraightButton_, 3, 2, 1, 1);

    scoreLayout->addWidget(new QLabel("Yatzy:", this), 4, 0, 1, 1);
    scoreLayout->addWidget(&yatzyScoreLabel_, 4, 1, 1, 1);
    scoreLayout->addWidget(&scoreYatzyButton_, 4, 2, 1, 1);
    
    scoreLayout->addWidget(new QLabel("Total:", this), 5, 0, 1, 1);
    scoreLayout->addWidget(&totalScoreLabel_, 5, 1, 1, 1);
    scoreLayout->setColumnStretch(2, 2);

    layout->addWidget(scoreTable, 7, 0, 1, YatzyRules::NUMBER_OF_DICE);
    layout->addWidget(&resetButton_, 8, 0, 1, 1);
    layout->addWidget(&quitButton_, 8, YatzyRules::NUMBER_OF_DICE-1, 1, 1);

    setLayout(layout);
}
