/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: gamerules.cc                                                        #
# Description: Module for the project 'Korttipeli'                          #
#       This module acts as the rules of the game.                          #
#############################################################################
*/

#include "gamerules.hh"

// Jos kukaan ei menny yli 21, tarkistetaan että kumpi on lähempänä 21, pelaaja
// voittaa jos tasapeli.
bool GameRules::checkIfPlayerWon(int player, int dealer)
{
    if (player == dealer) {
        return true;
    }

    else {
        if (dealer > player && dealer <= 21) {
        return false;
        }

        else {
            return true;
        }
    }
}

// Tarkistus funktio, joka käy tarkistaa onko kahdella ensimmäisellä kortilla
// saatu blackjack.
bool GameRules::checkIfBlackjack(std::vector<Card*> cards)
{
    int first_card = cards.at(0)->getValue();
    int second_card = cards.at(1)->getValue();

    if ((first_card == 1 && second_card == 10) ||
            (first_card == 10 && second_card == 1)) {
        return true;
    }

    else {
        return false;
    }
}
