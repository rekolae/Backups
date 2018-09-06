/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: deck.cc                                                             #
# Description: Module for the project 'Korttipeli'                          #
#       This module creates the card decks for the game to play with.       #
#############################################################################
*/

#include "deck.hh"

#include <QDragEnterEvent>
#include <QMimeData>


Deck::Deck(QWidget *parent) : QFrame(parent)
{
    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    // Tässä blackjack pelin versiossa käytetään 2 52-kortin pakkaa.
    for (int deck = 1; deck != 3; deck++) {
        for (int suit = SPADE; suit != SUIT_COUNT; ++suit){

            for (unsigned value = 1; value <= 13; ++value) {
                auto card = new Card(static_cast<CardSuit>(suit), value, this);
                int xOffset = (this->width() - card->width()) / 2;
                int yOffset = (this->height() - card->height()) / 2;
                card->move(xOffset, yOffset);
                cards_.push_back(card);
            }
        }
    }
    suffleDeck();
}

Card* Deck::pickCard()
{
    if (cards_.empty()){
        return nullptr;
    }

    else {
        Card* card = cards_.back();
        cards_.pop_back();
        return card;
    }
}

void Deck::addCard(Card* card)
{
    cards_.push_back(card);
    card->setParent(this);
    card->show();
}

// Suoritetaan, kun pakkaa klikataan.
void Deck::mousePressEvent(QMouseEvent *event)
{
    // Ohjelma ei saa kaatua tyhjän pakan klikkaukseen.
    if (cards_.empty()) {
        return;
    }

    // Otetaan osoittimen päähän pakan päällimmäinen kortti ja
    // poistetaan se pakasta.
    Card* card = cards_.back();
    cards_.pop_back();

    // Ohjelma ei saa kaatua, jos korttia ei olekaan.
    if (!card){
        return;
    }

    // Ilmoitetaan, että pakasta otettiin kortti.
    emit cardPicked();

    // Hyväksytään klikkaus, koska se käsitellään aina tässä metodissa.
    event->accept();
}

// Sekoitetaan kortit ennen pelin alkua.
void Deck::suffleDeck()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (cards_.begin(), cards_.end(), std::default_random_engine(seed));
}
