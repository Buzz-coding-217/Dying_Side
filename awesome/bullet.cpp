#include "splashkit.h"
#include "bullet.h"
#include "player.h"

//function that makes a bullet
bullet_data make_bullet(player_data &player)
{
    bullet_data bullet;

    //if the player is facing left side than the bullet will start from left side and if not then it will start from right side
    if(player.left_side == false)
    {
        bullet.bullet_sprite = create_sprite("bullet_right");
        bullet.bullet_x =player.player_x + 125;
        sprite_set_dx(bullet.bullet_sprite,1);              //the bullet will travel to right continously
    }
    else
    {
        bullet.bullet_sprite = create_sprite("bullet_left");
        bullet.bullet_x =player.player_x - 75;
        sprite_set_dx(bullet.bullet_sprite,-1);             //the bullet will travel to left continously
    }
    sprite_set_y(bullet.bullet_sprite,445);
    sprite_set_x(bullet.bullet_sprite,bullet.bullet_x);
    return bullet;
}

//drawing the bullet
void draw_bullet(bullet_data &draw)
{
    draw_sprite(draw.bullet_sprite);
}

//updating the bullet
void update_bullet(bullet_data &update)
{
    update_sprite(update.bullet_sprite);
}