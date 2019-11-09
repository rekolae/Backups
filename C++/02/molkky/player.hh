#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
public:
    Player(string name);
    string get_name();
    int get_points();
    int has_won();
    void add_points(int pts);

private:
    string name_;
    int points_;
};

#endif // PLAYER_HH
