#include "splashkit.h"
#include "player.h"
#include "zombies.h"
#include "dying_side.h"
#include "bullet.h"
#include <vector>
using namespace std;

// function which return the game data
game_data new_game()
{
    game_data game;
    game.player = new_player();
    game.game_over = false;
    game.kills = 0;
    game.level = 1;
    game.display_level_switch = UP;
    return game;
}

// introducting the game to the user
void intro()
{
    process_events();
    draw_bitmap("wallpaper", 0, 0);
    draw_text("DYING SIDE", COLOR_DARK_RED, "font", 55, 190, 270, option_to_screen());
    draw_text("PRESS SPACE TO START", COLOR_DARK_RED, "font", 35, 140, 390, option_to_screen());
    refresh_screen();
}

// displaying the level of the game at a certain point
void display_level(game_data &game)
{
    clear_screen();
    draw_bitmap("wallpaper", 0, 0, option_to_screen());
    draw_text("LEVEL" + to_string(game.level), COLOR_DARK_RED, "font", 55, 210, 330, option_to_screen());
    refresh_screen();
    delay(1000);
}

// adding zombies to the game
void add_zombie(game_data &game)
{
    game.zombies.push_back(make_zombie());
}

// adding the bullet to the game
void add_bullet(game_data &game)
{
    game.bullets.push_back(make_bullet(game.player));
}

// removing the zombies from game
void remove_zombie(game_data &game, int index)
{
    int last_index = game.zombies.size() - 1;
    game.zombies[index] = game.zombies[last_index];
    game.zombies.pop_back();
}

// removing the bullet from the game
void remove_bullet(game_data &game, int index)
{
    int last_index = game.bullets.size() - 1;
    game.bullets[index] = game.bullets[last_index];
    game.bullets.pop_back();
}

// drawing the HUD of the game
void HUD_sources(game_data &game)
{
    draw_bitmap("HUD", 0, 0, option_to_screen());
    draw_text("LIFES: " + to_string(game.player.lifes), COLOR_GREEN, "HUD", 35, 20, 20, option_to_screen());
    draw_text("KILLS: " + to_string(game.kills), COLOR_RED, "HUD", 35, 20, 65, option_to_screen());
    draw_text("BULLETS: " + to_string(game.player.bullets), COLOR_BLUE, "HUD", 35, 20, 115, option_to_screen());
}

// drawing the game
void draw_game(game_data &game)
{
    draw_bitmap("background", 0, 0, option_to_screen());
    draw_bitmap("air_ballon", 440, 30);
    HUD_sources(game);
    for (int i = 0; i < game.zombies.size(); i++)
    {
        draw_zombie(game.zombies[i]);
    }
    for (int i = 0; i < game.bullets.size(); i++)
    {
        draw_bullet(game.bullets[i]);
    }
    draw_player(game.player);
    refresh_screen();
}

// updating the game
void update_game(game_data &game)
{
    update_player(game.player);
    for (int i = 0; i < game.zombies.size(); i++)
    {
        update_zombie(game.zombies[i]);
    }
    for (int i = 0; i < game.bullets.size(); i++)
    {
        update_bullet(game.bullets[i]);
    }

    // different levels will have different probablity of zombies poping out
    if (game.level == 1)
    {
        if (rnd() < 0.001)
        {
            add_zombie(game);
            if (rnd() < 0.3)
            {
                play_sound_effect("zombie_roar");
            }
        }
    }
    else if (game.level == 2)
    {
        if (rnd() < 0.002)
        {
            add_zombie(game);
            if (rnd() < 0.2)
            {
                play_sound_effect("zombie_roar");
            }
        }
    }
    else if (game.level == 3)
    {
        if (rnd() < 0.004)
        {
            add_zombie(game);
            if (rnd() < 0.1)
            {
                play_sound_effect("zombie_roar");
            }
        }
    }

    // if there are bullets left and we press SPACE then bullet will fire and bullet firing sound will be played
    if (key_typed(SPACE_KEY) and game.player.bullets > 0)
    {
        add_bullet(game);
        game.player.bullets--;
        play_sound_effect("fire");
    }
    // if there are no bullets left and still SPACE is pressed then no bullet will fire and empty gun sound will play
    if (key_typed(SPACE_KEY) and game.player.bullets == 0)
    {
        play_sound_effect("empty");
    }
    check_collision(game);

    // if there are no lifes left then the game is over
    if (game.player.lifes == 0)
    {
        game.game_over = true;
    }
    // if we eliminate a certain number of zombies then level will increase
    if (game.kills == 15)
    {
        game.level = 2;
    }
    if (game.kills == 30)
    {
        game.level = 3;
    }

    // if we eliminate a certain number of zombies then the game will end and it will show you win
    if (game.kills == 60)
    {
        game.game_over = true;
    }

    // displaying the level with three lives, different bullets and all the zombies removed with the starting position of player
    if (game.level == 2 and game.display_level_switch == UP)
    {
        display_level(game);
        game.zombies.clear();
        game.player.player_x = STARTING_POINT;
        sprite_set_x(game.player.player_sprite, game.player.player_x);
        game.player.lifes = 3;
        game.player.bullets = 20;
        set_camera_x(0);
        game.display_level_switch = DOWN;
    }
    if (game.level == 3 and game.display_level_switch == DOWN)
    {
        display_level(game);
        game.zombies.clear();
        game.player.player_x = STARTING_POINT;
        sprite_set_x(game.player.player_sprite, game.player.player_x);
        game.player.lifes = 3;
        game.player.bullets = 30;
        set_camera_x(0);
        game.display_level_switch = UP;
    }
}

// checking the collision
void check_collision(game_data &game)
{
    // if zombie get hit with bullet, both of them will be removed and kill count will increment
    for (int i = 0; i < game.zombies.size(); i++)
    {
        for (int j = 0; j < game.bullets.size(); j++)
        {
            bool collision_bullet = sprite_collision(game.zombies[i].zombie_sprite, game.bullets[j].bullet_sprite);
            if (collision_bullet == true)
            {
                remove_zombie(game, i);
                remove_bullet(game, j);
                game.kills++;
            }
        }
    }
    // if zombie get to the player life will be reduced and sound of bite will be played
    for (int i = 0; i < game.zombies.size(); i++)
    {
        bool player_collision = sprite_collision(game.zombies[i].zombie_sprite, game.player.player_sprite);
        if (player_collision == true)
        {
            remove_zombie(game, i);
            game.player.lifes--;
            play_sound_effect("bite");
        }
    }
}

// displaying a game over screen depends upon our game
void game_over(game_data &game)
{
    draw_bitmap("wallpaper", 0, 0, option_to_screen());
    // if we die the game over screen will display we died
    if (game.player.lifes == 0)
    {
        draw_text("You Died!", COLOR_DARK_RED, "font", 55, 210, 250, option_to_screen());
        draw_text("You Killed " + to_string(game.kills) + " Zombies", COLOR_DARK_RED, "font", 35, 160, 350, option_to_screen());
    }
    // if we successfully kill a certain number of zombies then it will show you won
    else
    {
        draw_text("You Won!", COLOR_DARK_RED, "font", 55, 210, 250, option_to_screen());
        draw_text("You Killed " + to_string(game.kills) + " Zombies", COLOR_DARK_RED, "font", 35, 160, 320, option_to_screen());
        draw_text("Good job!", COLOR_DARK_RED, "font", 30, 210, 370, option_to_screen());
    }
    refresh_screen();
    delay(4000);
}