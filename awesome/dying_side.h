#include "splashkit.h"
#include "player.h"
#include "zombies.h"
#include "bullet.h"
using namespace std;
using std::vector;
#ifndef dying_side
#define dying_side

//enum which is used as a switch
enum switchs
{
    UP,
    DOWN
};

//struct that defines game's data
struct game_data
{
    player_data player;
    vector<zombie_data> zombies;
    vector<bullet_data> bullets;
    bool game_over;
    int kills;
    int level;
    switchs display_level_switch;
};

game_data new_game();
void intro();
void add_zombie(game_data &game);
void draw_game(game_data &game);
void update_game(game_data &game);
void add_zombie(game_data &game);
void check_collision(game_data &game);
void game_over(game_data &game);
void display_level(game_data &game);

#endif