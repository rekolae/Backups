#include "dealer.hh"
//#include "mainwindow.hh"


#include <chrono>

Dealer::Dealer()
{
}

void Dealer::toPickOrNotToPick()
{
    if (dealer_sum_ < 16) {
        dummy();
        pickACard;

    }

    else if (dealer_sum_ > 16 && dealer_sum_ != 21) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        srand(seed);
        int randomized_int = rand() % 100 + 1;

        if (randomized_int > 50) {
            pickACard();
        }

        else {
            // check for winner
        }
    }
}

