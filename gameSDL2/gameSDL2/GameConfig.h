#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

// Centralized game configuration
// Makes it easy to adjust game balance and settings

namespace GameConfig
{
    // Game difficulty and balance
    const int INITIAL_COINS = 200;
    const int INITIAL_MARKS = 100;
    const int CHARACTER2_COST = 100;

    // Mark adjustments
    const int MARK_LOSS_POISON = 10;
    const int MARK_LOSS_POISON_CHAR2 = 0; // Character 2 immune to poison
    const int MARK_GAIN_HEAL = 10;
    const int MARK_LOSS_BOMB = 40;
    const int MARK_GAIN_SUPERHEAL = 30;

    // Performance settings
    const int TARGET_FPS = 60; // Increased from 30 for smoother gameplay
    const int FRAME_TIME_MS = 1000 / TARGET_FPS;

    // Player settings
    const int PLAYER_SPEED = 2; // Increased from 1 for better responsiveness

    // UI timing
    const int MESSAGE_DISPLAY_TIME_MS = 3000; // Reduced from 5000 for better UX
}

#endif // GAME_CONFIG_H
