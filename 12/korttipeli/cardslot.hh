/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: cardslot.hh                                                         #
# Description: Module for the project 'Korttipeli'                          #
#       This module creates and handels the cardslots where cards held are. #
#############################################################################
*/

#ifndef CARDSLOT_HH
#define CARDSLOT_HH

#include "gamerules.hh"
#include "card.hh"

#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class CardSlot: public QFrame
{
public:
    // Rakentaja ja metodi, jolla slotiin voidaan lisätä kortti.
    CardSlot(QWidget* parent = 0);
    void addCard(Card* card);

    // Itse toteutetut Qt:n widgetin raahaukseen liittyvät metodit.
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    // Apumetodeita dropEventin käyttöön.
    void parseNewCards(std::list<Card*>& newCards, QStringList& newCardsData);
    void setupNewCards(std::list<Card*>& newCards);

    // Päällimmäisenä oleva kortti on talletettu attribuutiksi, koska se
    // vaikuttaa siihen, mitä tähän slotiin saa raahata. Muut kortit ovat vain
    // tämän widgetin lapsia, ja niihin päästään tarvittaessa käsiksi Qt:n
    // parent-mekanismin avulla.
    Card* topCard_;
};

#endif // CARDSLOT_HH
