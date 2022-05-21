#include "Ltexture.h"
class Food :public LTexture
{
private:
    int PosX, PosY;

public:
    Food(/* args */);
    ~Food()
    {

    }
    int getPosX()
    {
        return PosX;
    }
    int getPosY()
    {
        return PosY;
    }
    void Disappear()
    {
        PosY = 500;
    }
    void render(SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);
    void Move(const int &acceleration);
};

