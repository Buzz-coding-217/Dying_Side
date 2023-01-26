#include "splashkit.h"
#include "player.h"
#include "zombies.h"
#include "dying_side.h"

int main()
{
    //loading the resources of the game
    load_resource_bundle("game_bundle","dying_side.txt");
    //opening a window
    open_window("Dying Side",1000,640);

    //untill the SPACE key is pressed it will show the intro of the game
    while(not quit_requested() and not key_typed(SPACE_KEY))
    {
        intro();
    }

    //making a new game
    game_data game;
    game = new_game();

    //started by displaying the level of game
    display_level(game);

    //processing the game untill game is over
    while (not quit_requested() and not game.game_over)
    {
        handle_input(game.player);
        update_game(game);
        draw_game(game);
    }

    //showing the game over screen depending upon the game
    game_over(game);
}