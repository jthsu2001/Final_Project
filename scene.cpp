#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *font_14 = NULL;


// function of menu
void menu_init(){
    font = al_load_ttf_font("./font/OCR-A.ttf",36,0);
    font_14 = al_load_ttf_font("./font/OCR-A.ttf",20,0);
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}
void menu_draw(){
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "Lunar Lander");
    al_draw_text(font_14, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+50 , ALLEGRO_ALIGN_CENTRE, "inpired by Atari");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
}
void menu_destroy(){
    al_destroy_font(font);
}

// function of game_scene
void game_scene_init(){
    character_init();
    stat_init();
    message_init();
    fuel_init();
    background = al_load_bitmap("./image/background.jpg");
}
void game_scene_draw(){
    al_draw_scaled_bitmap(background, 0, 0, 970, 529, 0, 0, 2160, 1200, 0);
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
    char score_cnt[7];
    int holder=snprintf(score_cnt, sizeof score_cnt, "%d", SCORE);

    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "Your Score:");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+50 , ALLEGRO_ALIGN_CENTRE, score_cnt);

};
void end_scene_destroy(){
    al_destroy_font(font);
};


