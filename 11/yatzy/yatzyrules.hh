#ifndef YATZYRULES_H
#define YATZYRULES_H

// Common declaration for Yatzy.
namespace YatzyRules
{
    const int NUMBER_OF_DICE = 5;
    const int ROLLS_PER_TURN = 3;

    // All available score patterns.
    enum ScoreCombination
    {
        ONES,
        //TWOS,
        //THREES,
        //FOURS,
        //FIVES,
        //SIXES,
        ONE_PAIR,
        TWO_PAIRS,
        //THREE_OF_A_KIND,
        //FOUR_OF_A_KIND,
        SMALL_STRAIGHT,
        //LARGE_STRAIGHT,
        //FULL_HOUSE,
        //CHANCE,
        YATZY
    };
}

#endif // YATZYRULES_H
