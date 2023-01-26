#include "splashkit.h"
using namespace std;
#ifndef ZOMBIE
#define ZOMBIE

//enum for different bitmap of zombie
enum zombie{
    LEFT_,
    IN_LEFT,
    RIGHT_,
    IN_RIGHT
};

//struct that defines zombie's data
struct zombie_data
{
    sprite zombie_sprite;
    int zombie_x;
    timer zombie_timer;
    string side;
};

zombie_data make_zombie();
void draw_zombie(zombie_data &draw);
void update_zombie(zombie_data &update);

#endif