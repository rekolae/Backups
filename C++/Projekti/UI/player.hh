#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

#include <string>
#include <utility>

namespace Student{

class Player : public Common::IPlayer
{

public:

    /**
     * @brief Player Constructor.
     * @param id Id of the player
     */
    explicit Player(int id);
    ~Player();

    /**
     * @brief getPlayer gets the player id.
     * @return The identifier of the player.
     * @post Exception quarantee: nothrow
     */
    int getPlayerId() const;

    /**
     * @brief setActionsLeft sets the player's remaining number of actions.
     * @param actionsLeft The number of actions left.
     * @post Actions left set to parameter value. Exception quarantee: nothrow
     */
    void setActionsLeft(unsigned int actionsLeft);

    /**
     * @brief getActionsLeft returns the amount of actions left for the player
     * @return amount of actions
     * @post Exception quarantee: nothrow
     */
    unsigned int getActionsLeft() const;

    /**
     * @brief setPlayerName Sets players name
     * @param name Players name
     */
    void setPlayerName(std::string name);

    /**
     * @brief getPlayerName Returns players name
     * @return Players name
     */
    std::string getPlayerName();

private:

    int playerId_;
    unsigned int actionsLeft_;
    std::string name_;

};
}

#endif // PLAYER_HH
