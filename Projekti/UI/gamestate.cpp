#include "gamestate.hh"

namespace Student{

GameState::GameState()
= default;

GameState::~GameState()
= default;


Common::GamePhase GameState::currentGamePhase() const
{
    return currentGamePhase_;
}


int GameState::currentPlayer() const
{
    return currentPlayerId_;
}


void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    currentGamePhase_ = nextPhase;
}


void GameState::changePlayerTurn(int nextPlayer)
{
    currentPlayerId_ = nextPlayer;
}
}
