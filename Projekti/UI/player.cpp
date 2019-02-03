#include "player.hh"


namespace Student{

Player::Player(int id):playerId_(id)
{

}


Player::~Player()
= default;


int Player::getPlayerId() const
{
    return playerId_;
}


void Player::setActionsLeft(unsigned int actionsLeft)
{
    actionsLeft_ = actionsLeft;
}


unsigned int Player::getActionsLeft() const
{
    return actionsLeft_;
}


void Player::setPlayerName(std::string name)
{
    name_ = std::move(name);

}


std::string Player::getPlayerName()
{
    return name_;
};

}
