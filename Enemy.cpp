#include "Enemy.h"
Enemy::Enemy(int _type,int _type2)
{
    PosX = 0;
    PosY = 0;
    type = _type;
    type2 = _type2;
    if(type == ON_GROUND)
    {
        // PosX = rand() % (SCREEN_WIDTH - ENEMY_POSITION_RANGE) + ENEMY_POSITION_RANGE;
        PosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
        // PosX = 0;
        if(type2 == 1)
		    PosY = GROUND + 32;
        else 
            PosY = GROUND + 12;
    }
    else 
    {
        // PosX = rand() % (SCREEN_WIDTH - ENEMY_POSITION_RANGE) + ENEMY_POSITION_RANGE;
        // PosX = 0;
        PosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
        // PosX = 0;

		PosY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
        
    }
}
Enemy::~Enemy()
{

}
void Enemy::Move(const int &acceleration){
    PosX += -(4 + acceleration);
	if (PosX + MAX_ENEMY_WIDTH < 0)
	{
		PosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;

		if (type == ON_AIR)
		{
			PosY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
		}
	}
}
void Enemy::render(SDL_Renderer* gRenderer, SDL_Rect* clip ){
    Render(PosX,PosY,gRenderer,clip);
}
