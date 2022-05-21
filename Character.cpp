#include "Character.h"
Character::Character(/* args */)
{
    PosX = SCREEN_WIDTH - 700;
    PosY = GROUND;
}

void Character::HandelEvent(SDL_Event &event,Mix_Chunk *gChunk)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            if (on_ground())
            {
                status = JUMP;
                
                Mix_PlayChannel(-1,gChunk,0);
            }
                
        }
    }
}
void Character::Move()
{
    if (status == JUMP && PosY >= 100)
    {
        PosY -= JUMP_SPEED;
    }
    if (PosY <= MAX_HEIGHT_JUMP)
    {
        status = FALL;
    }
    if (status == FALL && PosY < GROUND)
    {
        PosY += FALL_SPEED;
    }
}
void Character::Render(LTexture gCharacterTexture, 
                        SDL_Rect *current_clips, 
                        SDL_Renderer *render)
{
    gCharacterTexture.Render(PosX,PosY,render,current_clips);
}