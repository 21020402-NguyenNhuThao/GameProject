#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<iostream>

#define TITLE "Sunny"
#define SCREEN_WIDTH 926
#define SCREEN_HEIGHT 463

#define LAYERS 6
#define CHA_LAYERS 8
#define GROUND 376

//STATUS CHARACTER
#define JUMP 1
#define FALL 2
#define RUN 0
#define MAX_HEIGHT_JUMP 250

#define ENEMY_SPEED 5
#define ON_AIR 0
#define ON_GROUND 1
#define SLUG 1
#define ENEMY_MAX_HEIGHT 290
#define ENEMY_MIN_HEIGHT 310
#define MAX_ENEMY_WIDTH 100
#define ENEMY_POSITION_RANGE 250

//BUTTON
#define SMALL_BUTTON 1
#define COMMON_BUTTON 2
#define MUSIC_BUTTON 3
#define BUTTON_TOTAL 2

#define SPEED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1

#define TIME_MAX 1000
const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;
const int SOUND_BUTTON_WIDTH = 34;
const int SOUND_BUTTON_HEIGHT = 32;
enum BUTTON_STATUS{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    MOUSE_TOTAL = 2
};
enum SOUND_STATUS
{
    ON = 1,
    OFF = 0
};

const int PLAY_BUTON_POSX = 389;
const int PLAY_BUTTON_POSY= 151;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 258;
const int EXIT_BUTTON_POSX = 389;
const int EXIT_BUTTON_POSY = 367;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 463;
const int PAUSE_BUTTON_POSY = 0;
const int CONTINUE_BUTTON_POSX = 463;
const int CONTINUE_BUTTON_POSY = 0;
const int SOUND_BUTTON_POSX = 500;
const int SOUND_BUTTON_POSY = 0;

const int YOUR_SCORE_POSX = 670;
const int YOUR_SCORE_POSY = 20;
const int HIGHEST_POSX = 670;
const int HIGHEST_POSY = 40;
const int SCORE_POSX = 830;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 830;
const int HIGH_SCORE_POSY = 40;

const int MAX_BLOOD = 6;
