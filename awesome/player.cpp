#include "splashkit.h"
#include "player.h"
using namespace std;

//function which return a bitmap for different enum values of player
bitmap player_bitmap(player kind)
{
    switch (kind)
    {
    case LEFT:
        return bitmap_named("player_left");
    case LEFT_IN:
        return bitmap_named("in-left");
    case RIGHT:
        return bitmap_named("player_right");
    case RIGHT_IN:
        return bitmap_named("in-right");
    }
}

//making a new player
player_data new_player(){
    player_data player;
    player.player_sprite = create_sprite(player_bitmap(RIGHT));         //default is player facing right side
    player.player_x = STARTING_POINT;                                   //initialising the player position
    sprite_set_x(player.player_sprite,player.player_x);
    sprite_set_y(player.player_sprite,410);

    //adding differnet layer for animation and movement
    sprite_add_layer(player.player_sprite, player_bitmap(LEFT), "player-left");
    sprite_hide_layer(player.player_sprite,1);
    sprite_add_layer(player.player_sprite, player_bitmap(LEFT_IN), "in-left");
    sprite_hide_layer(player.player_sprite,2);
    sprite_add_layer(player.player_sprite, player_bitmap(RIGHT_IN), "in-right");
    sprite_hide_layer(player.player_sprite,3);
    //initialsing other values of player
    player.left_side = false;
    player.bullets = 30;
    player.lifes = 3;

    //making timers
    create_timer("left");
    create_timer("right");
    return player;
}
void handle_input(player_data &player){
    //inputting the key pressed
    process_events();
    //if right key is pressed player will change its position to right and sprite layer and play a sound
    if (key_typed(RIGHT_KEY))
    {
        start_timer("right");
        player.player_x += 25;
        sprite_set_x(player.player_sprite,player.player_x);
        sprite_set_y(player.player_sprite,400);
        sprite_hide_layer(player.player_sprite,0);
        sprite_hide_layer(player.player_sprite,1);
        sprite_show_layer(player.player_sprite,2);
        play_sound_effect("step-sound");
        player.left_side = false;           //boolean of left side is false because the player is facing right side
    }
    //if the key is pressed and the timer will start and if the timer exeed this range it will change the layer and player will be moved further
    if (timer_ticks("right") > 200)
    {
        player.player_x += 25;
        sprite_set_y(player.player_sprite,410);
        sprite_set_x(player.player_sprite,player.player_x);
        sprite_hide_layer(player.player_sprite,2);
        sprite_show_layer(player.player_sprite,0);
        reset_timer("right");               //timer will reset
        stop_timer("right");                //timer is stopped for now
    }
    //if left key is pressed player will change its position to left and sprite layer will change and a sound will be player
    if (key_typed(LEFT_KEY))
    {
        start_timer("left");
        player.player_x -= 25;
        sprite_set_x(player.player_sprite,player.player_x);
        sprite_hide_layer(player.player_sprite,0);
        sprite_hide_layer(player.player_sprite,2);
        sprite_hide_layer(player.player_sprite,1);
        sprite_show_layer(player.player_sprite,3);
        sprite_set_y(player.player_sprite,400);         //adjusting the y coordinate
        play_sound_effect("step-sound");
        player.left_side = true;            //boolean of left side is true because the player is now facing left side
    }
    //if the key is pressed and the timer left will start and if the timer exeed this range it will change the layer and player will be moved further
    if (timer_ticks("left") > 200)
    {
        player.player_x -= 25;
        sprite_set_y(player.player_sprite,410);
        sprite_set_x(player.player_sprite,player.player_x);
        sprite_hide_layer(player.player_sprite,3);
        sprite_show_layer(player.player_sprite,1);
        reset_timer("left");            //timer left is reset
        stop_timer("left");             //timer is stopped for now
    }
}

//drawing the player
void draw_player(const player_data &draw)
{
    draw_sprite(draw.player_sprite);
}

//updating the player
void update_player(player_data &update)
{
    update_sprite(update.player_sprite);

    //setting the boundary of the screen
    int left_edge = camera_x() + SCREEN_BOUNDARY;
    int right_edge = left_edge + screen_width() - 2 * SCREEN_BOUNDARY;

    point_2d player_center = center_point(update.player_sprite);

    //if the player go beyond the edges the screen will be shifted
    if (player_center.x < left_edge)
    {
        move_camera_by(player_center.x - left_edge,0);
    }
    else if (player_center.x > right_edge)
    {
        move_camera_by(player_center.x - right_edge,0);
    }

    //if the player go beyond the game boundaries it will be pushed back
    if(player_center.x < -GAME_BOUNDARY)
    {
        update.player_x = left_edge;
        sprite_set_x(update.player_sprite,left_edge);
    }
    else if(player_center.x > screen_width() + GAME_BOUNDARY)
    {
        update.player_x = right_edge - 150;
        sprite_set_x(update.player_sprite,update.player_x);
    }
}  