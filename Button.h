#include "LTexture.h"
// #include "GameBase.hpp"
class Button
{
private:
    SDL_Point position;

public:
    SOUND_STATUS sound_status ;
    BUTTON_STATUS current_status;
    Button(int x, int y)
    {
        position.x = x;
        position.y = y;
        sound_status = ON;
    }
    void setPosition(int x, int y)
    {
        position.x = x;
        position.y = y;
    }
    bool is_mouse_inside(SDL_Event *e, int size);
    void Render(SDL_Rect *current_clips, SDL_Renderer *gRenderer, LTexture gButtonTexture);
};
