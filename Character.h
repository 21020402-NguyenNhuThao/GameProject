#include "LTexture.h"
class Character
{
private:
    int PosX, PosY;
    int status;
    

public:
    Character(/* args */);
    const int JUMP_SPEED = 8;
    const int FALL_SPEED = 8;
    bool on_ground(){
        return PosY == GROUND;
    }
    int GetPosX(){
        return PosX;
    }
    int GetPosY(){
        return PosY;
    }
    int GetStatus(){
        return status;
    }
    void HandelEvent(SDL_Event &event,Mix_Chunk *gChunk);
    void Move();
    void Render( LTexture gCharacterTexture, SDL_Rect * current_clips, SDL_Renderer *render);
};

