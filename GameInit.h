#include "Ltexture.h"
#include "Character.h"
#include "Enemy.h"
#include "Food.h"
#include "Button.h"
#include <bits/stdc++.h>
void ScrollingBackGround(float scrollingOffSpeed[LAYERS],
                         LTexture gBackground[LAYERS], SDL_Renderer *render);
void CharacterControlFrame(int &frame);
void EnemyControlFrame(int &bee_frame, int &tree_frame, int &slug_frame, int &carrot_frame);
// void GenerateFood(Food &food, SDL_Rect (&gCarrotClips)[4], SDL_Renderer *gRenderer);
bool InitEnemy(Food &food, Enemy &bee, Enemy &tree, Enemy &slug, SDL_Renderer *gRenderer);

void GenerateEnemy(
    SDL_Rect (&gTreeClips)[4],
    SDL_Rect (&gBeeClips)[8],
    SDL_Rect (&gSlugClips)[4],
    SDL_Rect (&gCarrotClips)[4],
    SDL_Renderer *gRenderer);
bool EatingFood(Character character,
                SDL_Rect *char_clip,
                Food food,
                SDL_Rect *food_clip);
bool CheckCollisionEnemy(Character character,
                         SDL_Rect *char_clip,
                         Enemy enemy,
                         SDL_Rect *enemy_clip);
bool CheckCollision(Character character,
                    Enemy bee, Enemy tree,
                    Enemy slug,
                    SDL_Rect *char_clip, SDL_Rect *bee_clip,

                    SDL_Rect *tree_clip, SDL_Rect *slug_clip, Mix_Chunk *gChunk);
void RenderBlood(int const bloods, LTexture gBlood, LTexture gBloodTex, SDL_Renderer *gRenderer, SDL_Rect *blood);
bool StillLife(int &hurt, int &bloods, int &eat);
void HandlePlayButton(SDL_Event *e,
                      Button &PlayButton,
                      bool &QuitMenu,
                      bool &Play,
                      Mix_Chunk *gClick);
void HandleHelpButton(SDL_Event *e,
                      SDL_Rect gBackButton[2],
                      LTexture InstructionTexture,
                      LTexture gBackTexture,
                      Button &HelpButton, Button &BackButton,
                      bool &Quit, SDL_Renderer *gRenderer,
                      Mix_Chunk *gClick);
void HandelExitButton(SDL_Event *e,
                      Button &ExitButton,
                      bool &Quit,
                      Mix_Chunk *gClick);
void HandleContinueButton(Button ContinueButton,
    Button SoundButton,
    LTexture gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    bool& Game_State, Mix_Chunk* gClick);
void HandlePauseButton(SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    Button& PauseButton,
    Button ContinueButton,
    Button SoundButton,
    LTexture gContinueButtonTexture,
    bool& game_state,
    Mix_Chunk* gClick);
// void HandelContinueButton(SDL_Event *e, bool &Game_State,
//                           Button CONTINUE_BUTTON, LTexture gContinueButtonTexture,
//                           Button SOUND_BUTTON,
//                           SDL_Rect gContinueButton[2],
//                           SDL_Renderer *gRenderer, Mix_Chunk *gClick);
// void HandelPauseButton(SDL_Event *e, bool &Game_State,
//                        Button &PAUSE_BUTTON, LTexture gPauseButtonTexture,
//                        SDL_Rect gPauseButton[2],
//                        Button CONTINUE_BUTTON, LTexture gContinueButtonTexture,
                       
//                        SDL_Rect gContinueButton[2],
//                        Button SOUND_BUTTON,
//                        SDL_Renderer *gRenderer, Mix_Chunk *gClick);
void HandelSoundButton(SDL_Event *e, Button &SOUND_BUTTON, LTexture gSoundTexture,
                       SDL_Rect gSoundButton[2], SDL_Renderer *gRenderer, Mix_Chunk *gClick);
void DrawPlayerScore(LTexture gYourScoreTexture, LTexture gScore,
                     TTF_Font *gFont, SDL_Color textColor,
                     SDL_Renderer *gRenderer, const int &score);
void DrawHighestScore(LTexture gHighestScoreTexture, LTexture gHighestScore,
                      TTF_Font *gFont, SDL_Color textColor,
                      SDL_Renderer *gRenderer, const std::string &HighScore);
std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path,
                     const int &score,
                     const std::string &old_high_score);

int UpdateGameTimeAndScore(int &time, int &speed, int &score);
void DrawAndSelection(SDL_Event *e, bool &Play_Again,
                      LTexture gLoseTexture, SDL_Renderer *gRenderer);