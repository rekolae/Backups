/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: deck.hh                                                             #
# Description: Module for the project 'Korttipeli'                          #
#       This module creates the card decks for the game to play with.       #
#############################################################################
*/

#ifndef DECK_HH
#define DECK_HH

#include "card.hh"

#include <vector>
#include <QFrame>


class Deck : public QFrame
{
    Q_OBJECT

public:
    Deck(QWidget *parent = 0);

    // Korttipakasta voi nostaa päällimmäisen kortin.
    Card* pickCard();
    void addCard(Card* card);

signals:
    // Signaali, jonka pakka lähettää, kun kortti nostetaan.
    void cardPicked();

protected:
    // Itse toteutettu Qt:n widgetin klikkaamiseen liittyvä metodi.
    void mousePressEvent(QMouseEvent *event);

private:
    // Korttipakan sisältämät kortit ja sekoitus metodi.
    std::vector<Card*> cards_;
    void suffleDeck();
};

#endif // DECK_HH
