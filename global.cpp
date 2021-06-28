#include "global.h"

// variables for global usage
const float FPS = 120.0;
const int WIDTH = 2160;
const int HEIGHT = 1200;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
extern ALLEGRO_BITMAP *background=NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
