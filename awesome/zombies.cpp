#include "splashkit.h"
#include "zombies.h"
using namespace std;

//function of zombie to return a bitmap for different enum
bitmap zombie_bitmap(zombie kind)
{
    switch (kind)
    {
    case LEFT_:
        return bitmap_named("zombie_left");
    case IN_LEFT:
        return bitmap_named("zombie-in_left");
    case RIGHT_:
        return bitmap_named("zombie_right");
    case IN_RIGHT:
        return bitmap_named("zombie-in_right");
    }
}

//creating a new zombie
zombie_data make_zombie(){
    zombie_data zombie;
    //to create a zombie at different sides
    int random_side = rnd(0,2);
    if(random_side == 0)
    {
        zombie.side = "left";
    }
    else
    {
        zombie.side = "right";
    }
    //if left zombie is made it will be facing left side and will have different sprite layer
    if(zombie.side == "left"){
        zombie.zombie_sprite = create_sprite(zombie_bitmap(LEFT_));
        sprite_add_layer(zombie.zombie_sprite, zombie_bitmap(IN_LEFT),"zombie-in_left");
        sprite_hide_layer(zombie.zombie_sprite,1);
    }
    //if right zombie is made it will be facing right side and will have different sprite layer
    else
    {
        zombie.zombie_sprite = create_sprite(zombie_bitmap(RIGHT_));
        sprite_add_layer(zombie.zombie_sprite, zombie_bitmap(IN_RIGHT),"zombie-in_right");
        sprite_hide_layer(zombie.zombie_sprite,1);
    }
    //if zombie's side is left it will appear on right side
    if(random_side == 0)
        zombie.zombie_x = rnd(900,1300);
    //if zombie's side is right it will appear on left side
    else 
        zombie.zombie_x = rnd(-500,0);
    //creating a random name for timer using rnd integer which is later converted to string
    int random_timer = rnd(-1000,1000);
    zombie.zombie_timer = create_timer(to_string(random_timer));
    //defining the location of the zombie
    sprite_set_x(zombie.zombie_sprite,zombie.zombie_x);
    sprite_set_y(zombie.zombie_sprite,408);
    start_timer(zombie.zombie_timer);
    return zombie;
}
//drawing the zombie
void draw_zombie(zombie_data &draw)
{
    draw_sprite(draw.zombie_sprite);
}

//updating the zombie
void update_zombie(zombie_data &update)
{
    update_sprite(update.zombie_sprite);

    //if the timer exceed this range the zombie will change layer which is define by its side
    if(timer_ticks(update.zombie_timer) < 750)
    {
        sprite_set_y(update.zombie_sprite, 408);            //adjusting the y coordinate
        sprite_hide_layer(update.zombie_sprite,1);
        sprite_show_layer(update.zombie_sprite,0);
    }
    else if (timer_ticks(update.zombie_timer) > 750 && timer_ticks(update.zombie_timer) < 1500)
    {
        sprite_set_y(update.zombie_sprite, 400);
        sprite_hide_layer(update.zombie_sprite,0);
        sprite_show_layer(update.zombie_sprite,1);
    }
    //if it exceed this range it will move and its layer is returned back to its original
    else if(timer_ticks(update.zombie_timer) > 1500)
    {
        if(update.side == "left")
        {
            update.zombie_x = update.zombie_x - 25;
        }
        else
        {
            update.zombie_x = update.zombie_x + 25;
        }
        sprite_set_x(update.zombie_sprite,update.zombie_x);
        reset_timer(update.zombie_timer);       //timer is resetted
            
    }
}
