#include "LTexture.h"
class Enemy : public LTexture
{
private:
    int PosX, PosY;
    int type;
    int type2;
   
public:
    Enemy(int _type,int _type2 );
    ~Enemy();
    int getPosX(){
        return PosX;
    }
    int getPosY(){
        return PosY;
    }
    int getType(){
        return type;
    }
    int getType2()
    {
        return type2;
    }
    void Move(const int &acceleration);
    int GetSpeed(const int& acceleration){
        return ENEMY_SPEED + acceleration;
    }
    void render(SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

};

