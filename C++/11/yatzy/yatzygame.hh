#ifndef YATZYGAME_H
#define YATZYGAME_H

#include "yatzyrules.hh"

#include <vector>
#include <map>
#include <random>
class YatzyGame
{

public:
    // The constructor.
    YatzyGame(unsigned seedValueForRandomNumberGenerator = 0);

    // The destructor.
    ~YatzyGame();

    // Get the number of rolls remaining.
    unsigned int getNumberOfRollsLeft() const;

    // Roll all unkept die.
    // Returns the values of all the dice.
    std::vector<unsigned int> roll();

    // Check if the given die can be kept.
    bool canKeep(unsigned int dieNumber) const;

    // Marks the given die as keep for following rolls.
    void keepRoll(unsigned int dieNumber);

    // Checks if the given score combination can be scored.
    bool canScore(YatzyRules::ScoreCombination combination) const;

    // Scoring functions.
    // Return the number of points scored.
    unsigned int scoreOnes();
    unsigned int scoreOnePair();
    unsigned int scoreTwoPairs();
    unsigned int scoreSmallStraight();
    unsigned int scoreYatzy();

    // Gets the total score.
    unsigned int getTotalScore() const;

    // Resets the game.
    void reset();

private:

    // Resets the rolls at the end of a round.
    void resetRolls();

    // Counter for remaining rolls.
    int rollsLeft_;

    // The values of rolled dice.
    std::vector<unsigned int> dieRolls_;

    // Flags for kept die. A kept die is not rerolled until the round ends.
    std::vector<bool> keepDie_;

    // The scored points.
    // The key is the type of the score.
    // The value is the number of points scored.
    std::map<YatzyRules::ScoreCombination, unsigned int> scores_;
    std::default_random_engine randomEngine_;
};

#endif // YATZYGAME_H
