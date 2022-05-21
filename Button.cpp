#include "Button.h"
bool Button::is_mouse_inside(SDL_Event *e, int size)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        int button_width, button_height;
        if (size == SMALL_BUTTON)
        {
            button_width = SMALL_BUTTON_WIDTH;
            button_height = SMALL_BUTTON_HEIGHT;
        }
        else if(size == COMMON_BUTTON)
        {
            button_width = COMMON_BUTTON_WIDTH;
            button_height = COMMON_BUTTON_HEIGHT;
        }
        else
        {
            button_height = SOUND_BUTTON_HEIGHT;
            button_width = SOUND_BUTTON_WIDTH;
        }
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if (x < position.x || x > position.x + button_width || y < position.y || y > position.y + button_height)
            inside = false;
        return inside;
    }
    return false;
}
void Button::Render(SDL_Rect *current_clips,
                    SDL_Renderer *gRenderer,
                    LTexture gButtonTexture)
{
    gButtonTexture.Render(position.x,position.y,gRenderer,current_clips);
}