#include "Food.h"
Food::Food()
{
   PosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;

	PosY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
    // PosY = 0;
}
void Food::render(SDL_Renderer* gRenderer, SDL_Rect* clip )
{
    Render(PosX,PosY,gRenderer,clip);
}
void Food::Move(const int &acceleration)
{
    PosX += -(3 + acceleration);
	if (PosX + MAX_ENEMY_WIDTH < 0)
	{
		PosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
        PosY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
	}
}