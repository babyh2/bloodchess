#include "stdafx.h"
#include "GameState.h"

GameState::GameState()
{
    Reset();
}

void GameState::Reset()
{
    current_state_ = MENU;
    coins_ = GameConfig::INITIAL_COINS;
    marks_ = GameConfig::INITIAL_MARKS;
    selected_character_ = 1;
    character2_owned_ = false;
}

bool GameState::PurchaseCharacter2()
{
    if (coins_ >= GameConfig::CHARACTER2_COST && !character2_owned_)
    {
        coins_ -= GameConfig::CHARACTER2_COST;
        character2_owned_ = true;
        return true;
    }
    return false;
}
