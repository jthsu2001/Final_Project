#include "charater.h"

// the state of character
enum {MISSION = 0, EXPLODE};
float gravity = 0.1;
typedef struct character
{
    float x, y; // the position of image
    float angle;
    int width, height; // the width and height of image
    float h_velocity, v_velocity; //velocity of horizontal and vertical direction
    int score; //counts score
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *explode;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation


}Character;
ALLEGRO_TIMER *timer;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_FONT *stats = NULL;
void character_init(){
    // load character images
    char temp[50];
    sprintf( temp, "./image/lander.png");
    chara.img = al_load_bitmap(temp);
    // load explosion image
    char explode[50];
    sprintf( explode, "./image/explosion.png");
    chara.explode=al_load_bitmap(explode);
    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img);
    chara.height = al_get_bitmap_height(chara.img);
    chara.x = chara.width/2;
    chara.y = chara.height/2;
    chara.h_velocity=10;
    chara.angle=0;
    chara.dir = false;

    // initial the animation component
    chara.state = MISSION;
    chara.anime = 0;
    chara.anime_time = 30;

}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
    else if(chara.x>WIDTH/2||chara.y>HEIGHT/2||chara.x*chara.y<0){//lander going out of bounds
        chara.img=chara.explode;//change draw image to explode.png
        judge_next_window = true;//initiate next window
    }
}
void character_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        chara.v_velocity-=0.3*cosf(chara.angle);
        chara.h_velocity+=0.3*sinf(chara.angle);
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara.angle-=0.1/3.14159;
    }
    else if( key_state[ALLEGRO_KEY_D] ){
        chara.angle+=0.1/3.14159;
    }

    //updates position as (x, y)==(x0, y0)+dt*(ax, ay)
    chara.v_velocity+=(float)gravity;
    chara.y += chara.v_velocity*(1/FPS)*2;
    chara.x += chara.h_velocity*(1/FPS)*2;
    //printf("%f\n", sinf(chara.angle));
    character_draw();
}
void character_draw(){
    // with the state, draw corresponding image
    float center_x=chara.width/2+chara.x;
    float center_y=chara.height/2+chara.y;
    stat_draw();
    al_draw_scaled_rotated_bitmap(chara.img, chara.width/2, chara.height/2, chara.x, chara.y, 0.2, 0.2, chara.angle, 0);
    }
void character_destory(){
    al_destroy_bitmap(chara.img);
    stat_destroy();
}
void stat_init(){
    stats=al_load_ttf_font("./font/OCR-A.ttf",34,0);
}
void stat_draw(){
    char h_speed[15];
    char v_speed[15];
    char score[5];
    float temp=(float)chara.v_velocity*-1.0;
    int holder1 = snprintf(h_speed, sizeof h_speed, "%f", chara.h_velocity);
    int holder2 = snprintf(v_speed, sizeof v_speed, "%f", temp);
    al_draw_text(stats, al_map_rgb(255,255,255), 1900, 95, 0, h_speed);
    al_draw_text(stats, al_map_rgb(255,255,255), 1900, 150, 0, v_speed);
}
void stat_destroy(){
    al_destroy_font(stats);
}
