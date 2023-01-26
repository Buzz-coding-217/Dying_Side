#include "splashkit.h"
#ifndef PLAYER
#define PLAYER
#define STARTING_POINT 300
#define SCREEN_BOUNDARY 150
#define GAME_BOUNDARY 300

//enum for different bitmap of player sprite
enum player {
    LEFT,
    LEFT_IN,
    RIGHT,
    RIGHT_IN
};

//struct that define player's data
struct player_data
{
    sprite player_sprite;
    int player_x;
    bool left_side;
    int bullets;
    int lifes;
};
player_data new_player();
void handle_input(player_data &player);
void update_player(player_data &update);
void draw_player(const player_data &draw);

#endif
