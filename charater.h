#include "global.h"
#include<math.h>
#include<time.h>;

void character_init();
void character_process(ALLEGRO_EVENT event);
void character_update();
void character_draw();
void character_destroy();

void delay(int number_of_seconds);

bool check_color(ALLEGRO_COLOR c);

void stat_init();
void stat_draw();
void stat_destroy();

void message_init();
void message_draw();
void message_destroy();
