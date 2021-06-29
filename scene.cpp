#include "scene.h"

ALLEGRO_FONT *font = NULL;


// function of menu
void menu_init(){
    font = al_load_ttf_font("./font/pirulen.ttf",12,0);
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}
void menu_draw(){
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy(){
    al_destroy_font(font);
}

// function of game_scene
void game_scene_init(){
    character_init();
    stat_init();
    message_init();
    background = al_load_bitmap("./image/background.png");
    ALLEGRO_LOCKED_REGION *lock;
    lock = al_lock_bitmap(background, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
}
void game_scene_draw(){
    al_draw_scaled_bitmap(background, 0, 0, 1104, 602, 0, 0, 2160, 1200, 0);
    character_draw();
}
void game_scene_destroy(){
    al_destroy_bitmap(background);
    character_destroy();
}

//function of end game sequence
void end_scene_init(){
    font=al_load_ttf_font("./font/OCR-A.ttf",34,0);
}
void end_scene_draw(){
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "Your Score:");
};
void end_scene_destroy(){
    al_destroy_font(font);
};


