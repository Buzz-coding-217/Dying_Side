#include "splashkit.h"
#include "player.h"
using namespace std;
#ifndef BULLET
#define BULLET
#define BULLET_SPEED 1


//struct that define bullet's data
struct bullet_data
{
    sprite bullet_sprite;
    int bullet_x;
};

bullet_data make_bullet(player_data &player);
void draw_bullet(bullet_data &draw);
void update_bullet(bullet_data &update);

#endif