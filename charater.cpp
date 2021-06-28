#include "charater.h"

// the state of character
enum {MISSION = 0, THRUST, EXPLODE, SUCCESS};
float gravity = 0.0;
typedef struct character
{
    float x, y; // the position of image
    float angle;
    int width, height; // the width and height of image
    float h_velocity, v_velocity; //velocity of horizontal and vertical direction
    int score; //counts score
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img[3];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation


}Character;
ALLEGRO_TIMER *timer;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_FONT *stats = NULL;
ALLEGRO_FONT *message = NULL;
void character_init(){
    // load character images
    char temp[50];
    sprintf( temp, "./image/lander.png");
    chara.img[0] = al_load_bitmap(temp);
    // load explosion image
    char explode[50];
    sprintf( explode, "./image/explosion.png");
    chara.img[1]=al_load_bitmap(explode);
    // load thrust image
    char thrust[50];
    sprintf( thrust, "./image/thrust.png");
    chara.img[2]=al_load_bitmap(thrust);
    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img[0]);
    chara.height = al_get_bitmap_height(chara.img[0]);
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
void delay(int number_of_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + number_of_seconds);
}
void character_process(ALLEGRO_EVENT event){
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
        chara.state=MISSION;
    }
    else if(chara.x>WIDTH||chara.y>HEIGHT||chara.x*chara.y<0){//lander going out of bounds
        chara.state=EXPLODE;
        //judge_next_window = true;//initiate next window
    }

}
ALLEGRO_COLOR pixel;
bool check_collision(){
    ALLEGRO_COLOR pixel;
    int sloppy_x=(int)chara.x/*sinf(chara.angle)*chara.width*/;
    int sloppy_y=(int)chara.y/*cosf(chara.angle)*chara.height*/;
    pixel=al_get_pixel(background, 100, 600);
    printf("%f %f %f\n", &pixel.r, pixel.g, pixel.b);
    if(check_color(pixel)){
        //printf("%f %f %d %d\n", chara.x, chara.y, sloppy_x, sloppy_y);
        //printf("%f %f %f\n", pixel.r, pixel.g, pixel. b);
        return true;
    }
}

bool check_color(ALLEGRO_COLOR c){
    float r, g, b;
    al_unmap_rgb_f(c, &r, &g, &b);
    float d;
    d=r+g+b;
    //printf("%f\n", d);
    if (d>2.0)return true;
}

void character_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        chara.v_velocity-=0.3*cosf(chara.angle);
        chara.h_velocity+=0.3*sinf(chara.angle);
        chara.state=THRUST;
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara.angle-=0.1/3.14159;
    }
    else if( key_state[ALLEGRO_KEY_D] ){
        chara.angle+=0.1/3.14159;
    }
    else if(abs(chara.x-1200)<40&&abs(chara.y-1115)<3){
        chara.state=SUCCESS;
    }

    else if(check_collision()){
        chara.state=EXPLODE;
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
    stat_draw();
    if(chara.state==MISSION){
        al_draw_scaled_rotated_bitmap(chara.img[0], chara.width/2, chara.height/2, chara.x, chara.y, 1, 1, chara.angle, 0);
        }
    if(chara.state==THRUST){
        al_draw_scaled_rotated_bitmap(chara.img[2], chara.width/2, chara.height/2, chara.x, chara.y, 0.2, 0.2, chara.angle, 0);
        }
    else if (chara.state==EXPLODE){
        al_draw_scaled_rotated_bitmap(chara.img[1], chara.width/2, chara.height/2, chara.x, chara.y, 0.2, 0.2, chara.angle, 0);
    }
    else if (chara.state==SUCCESS){
        al_draw_text(message, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "success");

        judge_next_window=true;
    }
}
void character_destroy(){
    al_destroy_bitmap(chara.img[0]);
    al_destroy_bitmap(chara.img[1]);
    stat_destroy();
}

void message_init(){
    message=al_load_ttf_font("./font/OCR-A.ttf",34,0);
}
void message_draw(){
    printf("draw\n");
    //al_draw_text(message, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "success");
    //delay(1000);
    judge_next_window=true;
}
void message_destroy(){
    al_destroy_font(message);
}

void stat_init(){
    stats=al_load_ttf_font("./font/OCR-A.ttf",34,0);
}
void stat_draw(){
    char h_speed[15];
    char v_speed[15];
    char score[5];
    float temp=(float)chara.y*-1.0;
    int holder1 = snprintf(h_speed, sizeof h_speed, "%f", chara.x);
    int holder2 = snprintf(v_speed, sizeof v_speed, "%f", temp);
    al_draw_text(stats, al_map_rgb(255,255,255), 408, 353, 0, h_speed);
    al_draw_text(stats, al_map_rgb(255,255,255), 1900, 150, 0, v_speed);
}
void stat_destroy(){
    al_destroy_font(stats);
}
