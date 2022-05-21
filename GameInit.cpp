#include "GameInit.h"
void ScrollingBackGround(float scrollingOffSpeed[LAYERS],
                         LTexture gBackground[LAYERS], SDL_Renderer *render)
{
    float layer_speed[] = {0.01, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2};
    for (int i = 0; i < LAYERS; i++)
    {
        scrollingOffSpeed[i] -= layer_speed[i];
        if (scrollingOffSpeed[i] < -gBackground[i].GetWidth())
            scrollingOffSpeed[i] = 0;
        gBackground[i].Render(scrollingOffSpeed[i], 0, render);
        gBackground[i].Render(scrollingOffSpeed[i] + gBackground[i].GetWidth(), 0, render);
    }
}
void CharacterControlFrame(int &frame)
{
    frame++;
    if (frame / 8 >= 8)
        frame = 0;
}
void EnemyControlFrame(int &bee_frame, int &tree_frame, int &slug_frame, int &carrot_frame)
{
    bee_frame++;
    if (bee_frame / 8 >= 8)
        bee_frame = 0;
    tree_frame++;
    if (tree_frame / 4 >= 4)
        tree_frame = 0;
    slug_frame++;
    if (slug_frame / 4 >= 4)
        slug_frame = 0;
    carrot_frame++;
    if (carrot_frame / 4 >= 4)
        carrot_frame = 0;
}

bool InitEnemy(Food &food, Enemy &bee, Enemy &tree, Enemy &slug, SDL_Renderer *gRenderer)
{
    bool success = true;
    if (!(bee.LoadFromFile("C:/GameNew/imgs/enemy/bee.png", gRenderer)))
    {
        std::cout << "LOI " << SDL_GetError() << std::endl;
        success = false;
    }
    if (!(tree.LoadFromFile("imgs/enemy/piranha-plant-attack.png", gRenderer)))
    {
        std::cout << "LOI " << SDL_GetError() << std::endl;
        success = false;
    }
    if (!(slug.LoadFromFile("imgs/enemy/slug.png", gRenderer)))
    {
        std::cout << "LOI " << SDL_GetError() << std::endl;
        success = false;
    }

    if (!(food.LoadFromFile("imgs/food/carrot.png", gRenderer)))
    {
        std::cout << "LOI " << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}
void GenerateEnemy(
    SDL_Rect (&gTreeClips)[4],
    SDL_Rect (&gBeeClips)[8],
    SDL_Rect (&gSlugClips)[4],
    SDL_Rect (&gCarrotClips)[4],
    SDL_Renderer *gRenderer)
{

    for (int i = 0; i < 8; i++)
    {
        gBeeClips[i].x = 37 * i;
        gBeeClips[i].y = 0;
        gBeeClips[i].h = 39;
        gBeeClips[i].w = 37;
    }
    for (int i = 0; i < 4; i++)
    {
        gTreeClips[i].x = 61 * i;
        gTreeClips[i].y = 0;
        gTreeClips[i].h = 45;
        gTreeClips[i].w = 61;
    }
    for (int i = 0; i < 4; i++)
    {
        gSlugClips[i].x = 32 * i;
        gSlugClips[i].y = 0;
        gSlugClips[i].h = 21;
        gSlugClips[i].w = 32;
    }
    for (int i = 0; i < 4; i++)
    {
        gCarrotClips[i].w = 17;
        gCarrotClips[i].h = 19;
        gCarrotClips[i].x = 17 * i;
        gCarrotClips[i].y = 0;
    }
}
bool EatingFood(Character character,
                SDL_Rect *char_clip,
                Food food,
                SDL_Rect *food_clip)
{
    int left_character = character.GetPosX();
    int right_character = character.GetPosX() + char_clip->w;
    int top_character = character.GetPosY();
    int bottom_character = character.GetPosY() + char_clip->h;
    const int TRASH_PIXEL_1 = 7;
    const int TRASH_PIXEL_2 = 5;

    int left_carrot = food.getPosX() + TRASH_PIXEL_1;
    int right_carrot = food.getPosX() + food_clip->w - TRASH_PIXEL_1;
    int top_carrot = food.getPosY();
    int bottom_carrot = food.getPosY() + food_clip->h - TRASH_PIXEL_2;

    if (right_character >= left_carrot && left_character <= right_carrot)
    {
        if (top_character >= top_carrot && top_character <= bottom_carrot)
            return true;
        if (bottom_character >= top_carrot && bottom_character <= bottom_carrot)
            return true;
    }
    return false;
}
bool CheckCollisionEnemy(Character character,
                         SDL_Rect *char_clip,
                         Enemy enemy,
                         SDL_Rect *enemy_clip)
{
    // bool collision = false;

    int left_character = character.GetPosX();
    int right_character = character.GetPosX() + char_clip->w;
    int top_character = character.GetPosY();
    int bottom_character = character.GetPosY() + char_clip->h;
    if (enemy.getType() == ON_AIR)
    {
        const int TRASH_PIXEL_1 = 22;
        const int TRASH_PIXEL_2 = 18;

        int left_bat = enemy.getPosX() + TRASH_PIXEL_1;
        int right_bat = enemy.getPosX() + enemy_clip->w - TRASH_PIXEL_1;
        int top_bat = enemy.getPosY();
        int bottom_bat = enemy.getPosY() + enemy_clip->h - TRASH_PIXEL_2;

        if (right_character >= left_bat && left_character <= right_bat)
        {
            if (top_character >= top_bat && top_character <= bottom_bat)
                return true;
            if (bottom_character >= top_bat && bottom_character <= bottom_bat)
                return true;
        }
    }
    else
    {
        int TRASH_PIXEL_1;
        int TRASH_PIXEL_2;
        if (enemy.getType2() != SLUG)
        {
            TRASH_PIXEL_1 = 25;
            TRASH_PIXEL_2 = 30;
        }
        else
        {
            TRASH_PIXEL_1 = 15;
            TRASH_PIXEL_2 = 10;
        }

        int left_cactus = enemy.getPosX() + TRASH_PIXEL_1;
        int right_cactus = enemy.getPosX() + enemy_clip->w - TRASH_PIXEL_1;
        int top_cactus = enemy.getPosY() + TRASH_PIXEL_2;
        // int bottom_cactus = enemy.getPosY() + enemy_clip->h - TRASH_PIXEL_2;

        if (right_character >= left_cactus && left_character <= right_cactus)
        {
            if (bottom_character >= top_cactus)
                return true;
        }
    }
    return false;
}
bool CheckCollision(Character character,
                    Enemy bee, Enemy tree, Enemy slug,
                    SDL_Rect *char_clip, SDL_Rect *bee_clip,
                    SDL_Rect *tree_clip, SDL_Rect *slug_clip, Mix_Chunk *gChunk)
{
    if (CheckCollisionEnemy(character, char_clip, bee, bee_clip))
    {
        Mix_PlayChannel(-1, gChunk, 0);
        return true;
    }

    if (CheckCollisionEnemy(character, char_clip, tree, tree_clip))
    {
        Mix_PlayChannel(-1, gChunk, 0);
        return true;
    }
    if (CheckCollisionEnemy(character, char_clip, slug, slug_clip))
    {
        Mix_PlayChannel(-1, gChunk, 0);
        return true;
    }

    return false;
}
void RenderBlood(int const bloods, LTexture gBlood, LTexture gBloodTex, SDL_Renderer *gRenderer, SDL_Rect *blood)
{
    // gBloodTex.Render(0,0,gRenderer);
    int space = 40;
    for (int i = 0; i < bloods; i++)
    {

        gBlood.Render(5 + space, 5, gRenderer, blood);
        space += 23;
    }
}
bool StillLife(int &hurt, int &bloods, int &eat)
{
    if (hurt >= 7)
    {
        bloods--;
        hurt = 0;
    }
    if (bloods == 0)
    {
        return false;
    }
    if (eat >= 5)
    {
        if (bloods >= 5)
            bloods = 5;
        bloods++;
        eat = 0;
    }
    return true;
}
void HandlePlayButton(SDL_Event *e,
                      Button &PlayButton,
                      bool &QuitMenu,
                      bool &Play,
                      Mix_Chunk *gClick)
{
    if (e->type == SDL_QUIT)
    {
        QuitMenu = true;
    }
    if (PlayButton.is_mouse_inside(e, COMMON_BUTTON))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            PlayButton.current_status = MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            PlayButton.current_status = MOUSE_OVER;
            Mix_PlayChannel(-1, gClick, 0);
            Play = true;
            QuitMenu = true;

            break;
        }
    }
    else
    {
        PlayButton.current_status = MOUSE_OUT;
    }
}
void HandleHelpButton(SDL_Event *e,
                      SDL_Rect gBackButton[2],
                      LTexture InstructionTexture,
                      LTexture gBackTexture,
                      Button &HelpButton, Button &BackButton,
                      bool &Quit, SDL_Renderer *gRenderer,
                      Mix_Chunk *gClick)
{

    if (HelpButton.is_mouse_inside(e, COMMON_BUTTON))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            HelpButton.current_status = MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            HelpButton.current_status = MOUSE_OVER;
            Mix_PlayChannel(-1, gClick, 0);
            bool ReadDone = false;
            while (!ReadDone)
            {
                do
                {
                    if (e->type == SDL_QUIT)
                    {
                        ReadDone = true;
                        Quit = true;
                    }
                    else if (BackButton.is_mouse_inside(e, COMMON_BUTTON))
                    {
                        switch (e->type)
                        {
                        case SDL_MOUSEMOTION:
                            BackButton.current_status = MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            BackButton.current_status = MOUSE_OVER;
                            Mix_PlayChannel(-1, gClick, 0);
                            ReadDone = true;
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        BackButton.current_status = MOUSE_OUT;
                    }
                    InstructionTexture.Render(0, 0, gRenderer);

                    SDL_Rect *backbutton_current_clips = &gBackButton[BackButton.current_status];
                    BackButton.Render(backbutton_current_clips, gRenderer, gBackTexture);

                    SDL_RenderPresent(gRenderer);

                } while (SDL_PollEvent(e) != 0 && (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION));
            }

            break;
        }
    }
    else
    {
        HelpButton.current_status = MOUSE_OUT;
    }
}
void HandelExitButton(SDL_Event *e,
                      Button &ExitButton,
                      bool &Quit,
                      Mix_Chunk *gClick)
{
    if (ExitButton.is_mouse_inside(e, COMMON_BUTTON))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            ExitButton.current_status = MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            ExitButton.current_status = MOUSE_OVER;
            Quit = true;
            Mix_PlayChannel(-1, gClick, 0);
            break;
        }
    }
    else
    {
        ExitButton.current_status = MOUSE_OUT;
    }
}
void HandleContinueButton(Button ContinueButton,
    Button SoundButton,
    LTexture gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    bool& Game_State, Mix_Chunk* gClick)
{
    bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.is_mouse_inside(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.current_status = MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					ContinueButton.current_status = MOUSE_OVER;
					Mix_PlayChannel(-1, gClick, 0);
                    if(SoundButton.sound_status == ON)
					    Mix_ResumeMusic();
					Game_State = true;
					Back_To_Game = true;
				}
				break;
				}
			}
			else
			{
				ContinueButton.current_status = MOUSE_OUT;
			}
		
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.current_status];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}
void HandlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer, 
	SDL_Rect (&gContinueButton)[BUTTON_TOTAL], 
	Button& PauseButton, 
	Button ContinueButton, 
    Button SoundButton,
	LTexture gContinueButtonTexture, 
	bool &Game_State, 
	Mix_Chunk *gClick)
{
	if (PauseButton.is_mouse_inside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.current_status = MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.current_status = MOUSE_OVER;
			Mix_PlayChannel(-1, gClick, 0);
			Mix_PauseMusic();
			break;
		case SDL_MOUSEBUTTONUP:
			Game_State = false;
			HandleContinueButton(ContinueButton,SoundButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, gClick);
			break;
		}
	}
	else
	{
		PauseButton.current_status = MOUSE_OUT;
	}
}

void HandelSoundButton(SDL_Event *e, Button &SOUND_BUTTON, LTexture gSoundTexture,
                       SDL_Rect gSoundButton[2], SDL_Renderer *gRenderer, Mix_Chunk *gClick)
{
    if (SOUND_BUTTON.is_mouse_inside(e, MUSIC_BUTTON))
    {
        
        if (SOUND_BUTTON.sound_status == ON)
        {
            switch (e->type)
            {
            case SDL_MOUSEBUTTONDOWN:

                Mix_PlayChannel(-1, gClick, 0);
                Mix_PauseMusic();
                Mix_Pause(-1);
                Mix_HaltChannel(-1);
                break;
            case SDL_MOUSEBUTTONUP:
                SOUND_BUTTON.sound_status = OFF;
                break;
            }
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEBUTTONDOWN:

                Mix_PlayChannel(-1, gClick, 0);
                Mix_ResumeMusic();
                Mix_Resume(-1);
                
                break;
            case SDL_MOUSEBUTTONUP:
                SOUND_BUTTON.sound_status = ON;
                break;
            }
        }

        // if(e->type == SDL_MOUSEBUTTONDOWN && SOUND_BUTTON.sound_status == ON)
        // {
        //     Mix_PlayChannel(-1, gClick, 0);

        //         Mix_PausedMusic();
        //         SOUND_BUTTON.sound_status = OFF;
        // }
        // else if (e->type == SDL_MOUSEBUTTONDOWN && SOUND_BUTTON.sound_status == OFF)
        // {
        //     Mix_PlayChannel(-1, gClick, 0);

        //     Mix_ResumeMusic();
        //     SOUND_BUTTON.sound_status = ON;
        // }
    }
}
void DrawAndSelection(SDL_Event *e, bool &Play_Again,
                      LTexture gLoseTexture, SDL_Renderer *gRenderer)
{
    if (Play_Again)
    {
        bool End_Game = false;
        while (!End_Game)
        {
            while (SDL_PollEvent(e) != 0)
            {
                if (e->type == SDL_QUIT)
                {
                    End_Game = true;
                    Play_Again = false;
                }
                if (e->type == SDL_KEYDOWN)
                {
                    switch (e->key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        End_Game = true;
                        break;
                    case SDLK_ESCAPE:
                        End_Game = true;
                        Play_Again = false;
                        break;
                    }
                }
            }
            gLoseTexture.Render(0, 0, gRenderer, NULL);
            SDL_RenderPresent(gRenderer);
        }
    }
}
void DrawPlayerScore(LTexture gYourScoreTexture, LTexture gScore,
                     TTF_Font *gFont, SDL_Color textColor,
                     SDL_Renderer *gRenderer, const int &score)
{

    gYourScoreTexture.Render(YOUR_SCORE_POSX, YOUR_SCORE_POSY, gRenderer);
    if (gScore.LoadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
    {
        gScore.Render(SCORE_POSX, SCORE_POSY, gRenderer);
    }
}
void DrawHighestScore(LTexture gHighestScoreTexture, LTexture gHighestScore,
                      TTF_Font *gFont, SDL_Color textColor,
                      SDL_Renderer *gRenderer, const std::string &HighScore)
{
    gHighestScoreTexture.Render(HIGHEST_POSX, HIGHEST_POSY, gRenderer);
    if (gHighestScore.LoadFromRenderedText(HighScore, gFont, textColor, gRenderer))
    {
        gHighestScore.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
    }
}
std::string GetHighScoreFromFile(std::string path)
{
    std::fstream HighScoreFile;
    std::string highscore;

    HighScoreFile.open(path, std::ios::in);
    HighScoreFile >> highscore;

    return highscore;
}
void UpdateHighScore(std::string path,
                     const int &score,
                     const std::string &old_high_score)
{
    int oldHighScore = 0;
    std::fstream HighScoreFile;
    std::string newHighScore;
    std::stringstream ConvertToInt(old_high_score);

    HighScoreFile.open(path, std::ios::out);

    ConvertToInt >> oldHighScore;
    if (score > oldHighScore)
    {
        oldHighScore = score;
    }
    newHighScore = std::to_string(oldHighScore);

    HighScoreFile << newHighScore;
}
int UpdateGameTimeAndScore(int &time,
                           int &speed,
                           int &score)
{
    if (time == TIME_MAX)
    {
        speed += 0;
    }

    if (time > TIME_MAX)
    {
        time = 0;
    }
    if (time % 5 == 0)
    {
        score += SCORE_INCREASEMENT;
    }

    time += TIME_INCREASEMENT;

    return time;
}
