#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Commonfunc.h"
#include "GameConfig.h"

// Manages game state and player progression
// Separates game logic from rendering
class GameState
{
public:
    enum State
    {
        MENU,
        GAME,
        SHOP,
        RULES,
        WIN,
        LOSS,
        EXIT
    };

    GameState();

    // Reset to initial state (for restart)
    void Reset();

    // State management
    State GetCurrentState() const { return current_state_; }
    void SetState(State state) { current_state_ = state; }

    // Player stats
    int GetCoins() const { return coins_; }
    void SetCoins(int coins) { coins_ = coins; }
    void AddCoins(int amount) { coins_ += amount; }

    int GetMarks() const { return marks_; }
    void SetMarks(int marks) { marks_ = marks; }
    void AddMarks(int amount) { marks_ += amount; }

    // Character selection
    int GetSelectedCharacter() const { return selected_character_; }
    void SetSelectedCharacter(int character) { selected_character_ = character; }

    bool IsCharacter2Owned() const { return character2_owned_; }
    void SetCharacter2Owned(bool owned) { character2_owned_ = owned; }
    bool PurchaseCharacter2();

private:
    State current_state_;
    int coins_;
    int marks_;
    int selected_character_; // 1 or 2
    bool character2_owned_;
};

#endif // GAME_STATE_H
