/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: mainwindow.hh                                                       #
# Description: Module for the project 'Korttipeli'                          #
#       This module sets up and handels the frame of the UI for the program #
#############################################################################
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deck.hh"
#include "gamerules.hh"
#include "cardslot.hh"

#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void pickACard();

public slots:
    void addCard();
    void changeActiveSlot();
    void gameDialog(bool blackjack, bool player_won, bool went_over);

signals:
    void gameEnd(bool blackjack, bool player_won, bool went_over);

private:
    void setupLayout();

    // Talletetaan attribuutiksi widgetti, jota käsitellään pelin aikana paljon.
    Deck* deck_;

    // Julistetaan ohjelman käytön helpottavat pointerit.
    CardSlot* player_cardslot_;
    CardSlot* dealer_cardslot_;
    CardSlot* current_cardslot_;

    // Julistetaan apufunktiot.
    void dealer();
    void checkCardValues(std::vector<Card*>* slot);

    std::vector<Card*> dealer_cards_;
    std::vector<Card*> player_cards_;
    std::vector<Card*>* slot_cards_;

    int times_clicked_;
    bool dealer_turn_;
    int player_sum_;
    int dealer_sum_;
    int* current_slot_sum_;
};

#endif // MAINWINDOW_HH
