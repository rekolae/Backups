/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: mainwindow.cc                                                       #
# Description: Module for the project 'Korttipeli'                          #
#       This module sets up and handels the frame of the UI for the program #
#############################################################################
*/

#include "mainwindow.hh"

#include <QPushButton>
#include <QCoreApplication>
#include <QMessageBox>
#include <QProcess>
#include <QVBoxLayout>


// Alustetaan rakentajassa ohjelmaa varten tarvittavat asiat.
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setupLayout();
    this->setStyleSheet("background-color: teal;");
    connect(deck_, &Deck::cardPicked, this, &MainWindow::addCard);
    //connect(this, &MainWindow::closeGame, this, &MainWindow::shutDown);
    connect(this, &MainWindow::gameEnd, this, &MainWindow::gameDialog);
    times_clicked_ = 0;
    slot_cards_ = &player_cards_;
    current_slot_sum_ = &player_sum_;
}

MainWindow::~MainWindow()
{
}

// Luo ja asettaa olioiden paikat UI:ssa oikeille paikoilleen
void MainWindow::setupLayout()
{
    // Pääikkunan isoimpana rakenteena on frame, joka sisältää...
    QFrame* frame = new QFrame;
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    // ... ala-, keski- ja ylärivin.
    QHBoxLayout* bottomRowLayout = new QHBoxLayout();
    QHBoxLayout* middleRowLayout = new QHBoxLayout();
    QHBoxLayout* topRowLayout = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout);
    frameLayout->addLayout(middleRowLayout);
    frameLayout->addLayout(bottomRowLayout);

    // Luodaan pakkaolio.
    deck_ = new Deck(this);

    // Lisätään yläriville jakajan cardslot...
    dealer_cardslot_ = new CardSlot(this);
    dealer_cardslot_->setAcceptDrops(false);
    topRowLayout->addWidget(dealer_cardslot_);

    // ... keskelle suljettu pakka sekä vuoronlopetus nappi...
    middleRowLayout->addWidget(deck_);
    QPushButton* button = new QPushButton("Stand", this);
    button->setMaximumSize(70, 70);
    middleRowLayout->addWidget(button);
    connect(button, SIGNAL (clicked()), this, SLOT (changeActiveSlot()));

    // ... ja alas yksi pelaajan cardslot ja asetetaan se aktiiviseksi.
    player_cardslot_ = new CardSlot(this);
    current_cardslot_ = player_cardslot_;

    bottomRowLayout->addWidget(player_cardslot_);

    setCentralWidget(frame);
}

// Klikatessa UI:n "stand"-nappia vaihdetaan vuoro pelaajalta jakajalle.
void MainWindow::changeActiveSlot()
{
    current_cardslot_->setAcceptDrops(false);
    current_cardslot_ = dealer_cardslot_;
    current_cardslot_->setAcceptDrops(true);

    slot_cards_ = &dealer_cards_;
    current_slot_sum_ = &dealer_sum_;

    times_clicked_ = 0;
    dealer_turn_ = true;
    dealer();
}

// Luo popup ikkunan, jos huomataan tilanne että jompikumpi voitti pelin.
// Bool arvoja käytetään eri voitto/häviö tekstien luomiseen.
void MainWindow::gameDialog(bool blackjack, bool player_won, bool went_over)
{
    QString title = "You lost! :(";
    QString message = "Click yes if you want to play again, click no if you "
                      "want to quit";
    QString result;


    if (player_won) {
        title = "You won!!";
    }

    if (blackjack) {
            result = "%1 got a blackjack and won!!";

            if (player_won) {
                result = result.arg("You");
            }

            else {
                result = result.arg("Dealer");
            }
    }

    else if (went_over) {
        result = "%1 went over by getting %2 and lost!!";

        if (player_won) {
            result = result.arg("Dealer").arg(dealer_sum_);
        }

        else {
            result = result.arg("You").arg(player_sum_);
        }
    }

    else {
        result = "%1 won with a score of %2 against a score of %3";

        if (player_won) {
            result = result.arg("You").arg(player_sum_).arg(dealer_sum_);
        }

        else {
            result = result.arg("Dealer").arg(dealer_sum_).arg(player_sum_);
        }
    }

    // Luodaan popup dialogi-ikkuna, joka kertoo voittajan ja kysyy haluaako
    // käyttäjä pelata uuden pelin vaiko lopettaa.
    QMessageBox::StandardButton question = QMessageBox::information(this,
    QString(title), QString("%1 %2 %3").arg(result, "\n   \n", message),
    QMessageBox::No | QMessageBox::Yes);

    // Jos klikataan popup ikkunassa kyllä niin käynnistetään ohjelma uusiksi,
    // muutoin lopetetaan ohjelma.
    if(question == QMessageBox::Yes) {
        QProcess::startDetached(QCoreApplication::applicationFilePath());
        exit(12);
    }

    else {
        QCoreApplication::quit();
    }
}

// Nostaa pakasta kortin ja asettaa sen kyseisellä hetkellä aktiivisena olevaan
// cardslottiin.
void MainWindow::pickACard()
{
    times_clicked_++;
    Card* card = deck_->pickCard();
    current_cardslot_->addCard(card);
    card->show();
    card->turn();
    slot_cards_->push_back(card);
    checkCardValues(slot_cards_);
}

// Tarkistaa vectorissa olevien korttien perusteella mm. onko pelaaja/jakaja
// saanut blackjack tai mennyt yli 21.
void MainWindow::checkCardValues(std::vector<Card*>* slot)
{
    int sum = 0;
    for (Card* card : *slot) {
        int value = card->getValue();
        sum += value;
    }

    *current_slot_sum_ = sum;

    // Riippuen korteista lähetetään tietynlainen yhdistelmä bool arvoja,
    // joita käytetään popup ikkunan teksteissä.
    if (sum > 21 && current_cardslot_ == player_cardslot_) {
        emit gameEnd(false, false, true);
    }

    else if (sum > 21 && current_cardslot_ == dealer_cardslot_) {
        emit gameEnd(false, true, true);
    }

    else {
        if (times_clicked_ == 2 && current_cardslot_ == player_cardslot_) {
            if (GameRules::checkIfBlackjack(player_cards_)) {
                emit gameEnd(true, true, false);
            }
        }

        else if (times_clicked_ == 2 && current_cardslot_ == dealer_cardslot_) {
            if (GameRules::checkIfBlackjack(dealer_cards_)) {
                emit gameEnd(true, false, false);
            }
        }
    }
}

// Apufunktio mitä QObject voi kutsua.
void MainWindow::addCard()
{
    pickACard();
}

// Toimii pelin 'tekoälynä' pelaajaa vastaan, käyttää RNG:ia korttien nostoon
// liittyvässä arpomisessa
void MainWindow::dealer()
{
    // Pyörii kunnes 'tekoäly' päättää lopettaa tai menee yli 21.
    while (dealer_turn_ && dealer_sum_ <= 21) {

        if (dealer_sum_ < 15) {
            pickACard();
        }

        else if (dealer_sum_ >= 15 && dealer_sum_ < 20) {
            // Käytetään tietokoneen kelloa siemenen generoimiseen RNG:ia varten
            unsigned seed = std::chrono::system_clock::now()
                            .time_since_epoch().count();
            srand(seed);
            int randomized_int = rand() % 100 + 1;

            // Jos randomoitu numero on yli 50, nostetaan kortti.
            if (randomized_int > 50) {
                pickACard();
            }

            else {
                dealer_turn_ = false;
            }
        }

        else {
            dealer_turn_ = false;
        }
    }

    // 'Tekoälyn' lopettaessa vuoronsa tarkistetaan voittaja.
    if (GameRules::checkIfPlayerWon(player_sum_, dealer_sum_)) {
        emit gameEnd(false, true, false);
    }

    else {
        emit gameEnd(false, false, false);
    }
}
