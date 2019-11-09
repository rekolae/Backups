/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: gamerules.hh                                                        #
# Description: Module for the project 'Korttipeli'                          #
#       This module acts as the rules of the game.                          #
#############################################################################
*/

#ifndef GAMERULES_HH
#define GAMERULES_HH

#include <card.hh>

namespace GameRules {
    bool checkIfPlayerWon(int player, int dealer);
    bool checkIfBlackjack(std::vector<Card*> cards);
}

#endif // GAMERULES_HH
