#include "GameInit.h"
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

//
const std::string LAYER[LAYERS]{
    "imgs/background/background1.png",
    "imgs/background/background2.png",
    "imgs/background/background3.png",
    "imgs/background/background4.png",
    "imgs/background/background5.png",
    "imgs/background/background6.png"};
LTexture gBackground[LAYERS];
LTexture gBoardTexture;
LTexture gCharacterTexture;
LTexture gTreeTexture;
LTexture gBeeTexture;
LTexture gBlood;
LTexture gBloodTex;
LTexture gYourScoreTexture;
LTexture gHighestScoreTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gMenuTexture;
LTexture gLoseTexture;
LTexture gInstructionTexture;
LTexture gScore;
LTexture gHighScore;
LTexture gStatusTexture;
LTexture gStatusNormalTexture;
LTexture gSoundTexture;

SDL_Color textColor = {255, 165, 0};
TTF_Font *gFont = nullptr;
Mix_Music *gMusic = nullptr;
Mix_Music *gMenuMusic = nullptr;
Mix_Chunk *gClick = nullptr;
Mix_Chunk *gJump = nullptr;
Mix_Chunk *gLose = nullptr;
Mix_Chunk *gEat = nullptr;
Mix_Chunk *gMouseClick = nullptr;

SDL_Rect gCharacterClips[CHA_LAYERS];
SDL_Rect gTreeClips[4];
SDL_Rect gBeeClips[8];
SDL_Rect gSlugClips[4];
SDL_Rect gCarrotClips[4];
SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gStatusHurt[2];
SDL_Rect gStatusNormal[9];
SDL_Rect gSoundButton[2];

Button BACK_BUTTON(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button CONTINUE_BUTTON(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button EXIT_BUTTON(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button HELP_BUTTON(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button PAUSE_BUTTON(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button PLAY_BUTTON(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button SOUND_BUTTON(SOUND_BUTTON_POSX,SOUND_BUTTON_POSY);

bool init();
bool loadMedia();
void close();

float scrollingOff[6];

int main(int argc, char *args[])
{

    if (init())
    {
        if (loadMedia())
        {
            bool Quit_Menu = false;
            bool Play_Again = false;
            Mix_PlayMusic(gMenuMusic, -1);
            while (!Quit_Menu)
            {
                SDL_Event e_mouse;
                while (SDL_PollEvent(&e_mouse) != 0)
                {
                    if (e_mouse.type == SDL_QUIT)
                    {
                        Quit_Menu = true;
                    }
                    else
                    {
                        bool Quit_Game = false;
                        HandlePlayButton(&e_mouse, PLAY_BUTTON,
                                         Quit_Menu, Play_Again,
                                         gMouseClick);
                        HandleHelpButton(&e_mouse, gBackButton,
                                         gInstructionTexture, gBackButtonTexture,
                                         HELP_BUTTON, BACK_BUTTON,
                                         Quit_Menu, gRenderer, gMouseClick);
                        HandelExitButton(&e_mouse, EXIT_BUTTON, Quit_Menu, gMouseClick);
                        if (Quit_Game == true)
                        {
                            return 0;
                        }
                    }
                }
                gMenuTexture.Render(0, 0, gRenderer, NULL);

                SDL_Rect *current_Play_clips = &gPlayButton[PLAY_BUTTON.current_status];
                PLAY_BUTTON.Render(current_Play_clips, gRenderer, gPlayButtonTexture);

                SDL_Rect *current_Help_clips = &gHelpButton[HELP_BUTTON.current_status];
                HELP_BUTTON.Render(current_Help_clips, gRenderer, gHelpButtonTexture);

                SDL_Rect *current_Exit_clips = &gExitButton[EXIT_BUTTON.current_status];
                EXIT_BUTTON.Render(current_Exit_clips, gRenderer, gExitButtonTexture);

                SDL_RenderPresent(gRenderer);
            }
            while (Play_Again)
            {
                bool quit = false;
                bool Game_State = true;
                srand(time(NULL));
                Enemy bee(ON_AIR, 0);
                Enemy tree(ON_GROUND, 0);
                Enemy slug(ON_GROUND, 1);
                Food food;
                SDL_Event e;
                int time = 0;
                int score = 0;
                for (int i = 0; i < LAYERS; i++)
                    scrollingOff[i] = 0;
                Character character;
                int bloods = MAX_BLOOD;
                int eat = 0;
                int hurt = 0;
                int character_frame = 0;
                int bee_frame = 0;
                int tree_frame = 0;
                int slug_frame = 0;
                int carrot_frame = 0;
                int status_hurt_frame = 0;
                int status_normal_frame = 0;
                int acceleration = 0;
                SOUND_BUTTON.sound_status = ON;
                std::string highscore = GetHighScoreFromFile("high_score.txt");
                Mix_PlayMusic(gMusic, -1);
                if (!(InitEnemy(food, bee, tree, slug, gRenderer)))
                {
                    std::cout << "LOOOO";
                }

                GenerateEnemy(gTreeClips, gBeeClips, gSlugClips, gCarrotClips, gRenderer);
                while (!quit)
                {
                    
                    
                    if(Game_State)
                    {
                        UpdateGameTimeAndScore(time, acceleration, score);
                         while (SDL_PollEvent(&e))
                        {
                            if (e.type == SDL_QUIT)
                            {
                                quit = true;
                            }
                            character.HandelEvent(e, gJump);
                            HandlePauseButton(&e,gRenderer,gContinueButton,PAUSE_BUTTON,CONTINUE_BUTTON,SOUND_BUTTON,gContinueButtonTexture,Game_State,gClick);
                            
                            HandelSoundButton(&e,SOUND_BUTTON,gSoundTexture,gSoundButton,gRenderer,gClick);
                        }
                        if (!StillLife(hurt, bloods, eat))
                        {
                            quit = true;
                            Mix_PauseMusic();
                            Mix_PlayChannel(-1, gLose, 0);
                            UpdateHighScore("high_score.txt", score, highscore);
                        }
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);
                        // Scrolling Background and Ground
                        ScrollingBackGround(scrollingOff, gBackground, gRenderer);
                        gBoardTexture.Render(650, 15, gRenderer);
                        // Status

                        if (bloods < 3)
                        {

                            SDL_Rect *status_current_clips = &gStatusHurt[status_hurt_frame / 2];
                            gStatusTexture.Render(0, 0, gRenderer, status_current_clips);
                            status_hurt_frame++;
                            if (status_hurt_frame / 2 >= 2)
                            {
                                status_hurt_frame = 0;
                            }
                        }
                        else
                        {
                            SDL_Rect *status_current_clips = &gStatusNormal[status_normal_frame/9];
                            gStatusNormalTexture.Render(0,0,gRenderer,status_current_clips);
                            status_normal_frame++;
                            if (status_normal_frame / 9 >= 9)
                            {
                                status_normal_frame = 0;
                            }
                        }

                        // Blood
                        SDL_Rect *blood = nullptr;
                        RenderBlood(bloods, gBlood, gBloodTex, gRenderer, blood);
                        // Character
                        character.Move();
                        SDL_Rect *current_clips = nullptr;
                        if (character.on_ground())
                        {
                            current_clips = &gCharacterClips[character_frame / 8];
                            character.Render(gCharacterTexture, current_clips, gRenderer);
                        }
                        else
                        {
                            current_clips = &gCharacterClips[0];
                            character.Render(gCharacterTexture, current_clips, gRenderer);
                        }
                        // Bee
                        bee.Move(acceleration);
                        SDL_Rect *bee_current_clips = &gBeeClips[bee_frame / 8];
                        bee.render(gRenderer, bee_current_clips);
                        // tree
                        tree.Move(acceleration);
                        SDL_Rect *tree_current_clips = &gTreeClips[tree_frame / 4];
                        tree.render(gRenderer, tree_current_clips);
                        // Slug
                        slug.Move(acceleration);
                        SDL_Rect *slug_current_clips = &gSlugClips[slug_frame / 4];
                        slug.render(gRenderer, slug_current_clips);
                        // Carrot
                        SDL_Rect *carrot_current_clips = &gCarrotClips[carrot_frame / 4];
                        food.Move(acceleration);
                        food.render(gRenderer, carrot_current_clips);
                        if (EatingFood(character, current_clips, food, carrot_current_clips))
                        {
                            eat++;
                            food.Disappear();
                            current_clips = &gCharacterClips[0];
                        }
                        if (CheckCollision(character, bee, tree, slug, current_clips, bee_current_clips, tree_current_clips, slug_current_clips, gLose))
                        {
                            hurt++;
                            current_clips = &gCharacterClips[0];
                        }
                        
                        SDL_Rect *current_Pause_clips = &gPauseButton[PAUSE_BUTTON.current_status];
                        PAUSE_BUTTON.Render(current_Pause_clips,gRenderer,gPauseButtonTexture);

                        SDL_Rect *current_Sound_clips = &gSoundButton[SOUND_BUTTON.sound_status];
                        SOUND_BUTTON.Render(current_Sound_clips,gRenderer,gSoundTexture);


                        DrawPlayerScore(gYourScoreTexture, gScore, gFont, textColor, gRenderer, score);
                        DrawHighestScore(gHighestScoreTexture, gHighScore, gFont, textColor, gRenderer, highscore);
                        SDL_RenderPresent(gRenderer);
                        CharacterControlFrame(character_frame);
                        EnemyControlFrame(bee_frame, tree_frame, slug_frame, carrot_frame);
                        SDL_Delay(10);

                    }    
                }
                DrawAndSelection(&e, Play_Again, gLoseTexture, gRenderer);
                if (!Play_Again)
				{
					tree.~Enemy();
					bee.~Enemy();
					slug.~Enemy();
				}
            }
        }
    }
    close();
    return 0;
}
bool init()
{
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(TITLE,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   926,
                                   463, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cout << "Unable to init window" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
            if (gRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                success = false;
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                std::cout << "SDL_mixer could not initialize! SDL_Mixer Error: " << Mix_GetError() << std::endl;
                success = false;
            }
            if (TTF_Init() == -1)
            {
                std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}
bool loadMedia()
{
    bool success = true;
    // Init TTF
    gFont = TTF_OpenFont("font/somepx.ttf", 28);
    if (!(gBloodTex.LoadFromRenderedText("BLOOD ", gFont, textColor, gRenderer)))
    {
        std::cout << "Failed to load text 1 " << std::endl;
        success = false;
    }
    if (!(gYourScoreTexture.LoadFromRenderedText("Your Score: ", gFont, textColor, gRenderer)))
    {
        std::cout << "Failed to load text 1 " << std::endl;
        success = false;
    }
    if (!(gHighestScoreTexture.LoadFromRenderedText("High Score: ", gFont, textColor, gRenderer)))
    {
        std::cout << "Failed to load text 2 " << std::endl;
        success = false;
    }
    // Init Menu Instruction
    if (!(gInstructionTexture.LoadFromFile("imgs/background/instruction.png", gRenderer)))
    {
        std::cout << "Failed to load instructionimg " << SDL_GetError() << std::endl;
        success = false;
    }
    if (!(gBoardTexture.LoadFromFile("imgs/background/board.png", gRenderer)))
    {
        std::cout << "Failed to load menu img " << SDL_GetError() << std::endl;
        success = false;
    }
    if (!(gMenuTexture.LoadFromFile("imgs/background/Menu.png", gRenderer)))
    {
        std::cout << "Failed to load menu img " << SDL_GetError() << std::endl;
        success = false;
    }
    if (!(gLoseTexture.LoadFromFile("imgs/background/lose.png", gRenderer)))
    {
        std::cout << "Failed to load lose img " << SDL_GetError() << std::endl;
        success = false;
    }
    // Init Button
    if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
    {
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gPlayButton[i].x = 150 * i;
            gPlayButton[i].y = 0;
            gPlayButton[i].w = 150;
            gPlayButton[i].h = 98;
        }
    }

    if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", gRenderer))
    {
        std::cout << "Failed to load help_button image" << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gHelpButton[i].x = 150 * i;
            gHelpButton[i].y = 0;
            gHelpButton[i].w = 150;
            gHelpButton[i].h = 98;
        }
    }

    if (!gBackButtonTexture.LoadFromFile("imgs/button/big_button/back_button.png", gRenderer))
    {
        std::cout << "Failed to load back_button image" << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gBackButton[i].x = 100 * i;
            gBackButton[i].y = 0;
            gBackButton[i].w = 100;
            gBackButton[i].h = 78;
        }
    }

    if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer))
    {
        std::cout << "Failed to load exit_button image" << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gExitButton[i].x = 150 * i;
            gExitButton[i].y = 0;
            gExitButton[i].w = 150;
            gExitButton[i].h = 98;
        }
    }

    if (!gPauseButtonTexture.LoadFromFile("imgs/button/big_button/pause_button.png", gRenderer))
    {
        std::cout << "Failed to load pause_button image " << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gPauseButton[i].x = 22 * i;
            gPauseButton[i].y = 0;
            gPauseButton[i].w = 22;
            gPauseButton[i].h = 34;
        }
    }

    if (!gContinueButtonTexture.LoadFromFile("imgs/button/big_button/continue_button.png", gRenderer))
    {
        std::cout << "Failed to load continue_button image " << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gContinueButton[i].x = 22 * i;
            gContinueButton[i].y = 0;
            gContinueButton[i].w = 22;
            gContinueButton[i].h = 34;
        }
    }
    if(!(gSoundTexture.LoadFromFile("imgs/button/Sound.png",gRenderer)))
    {
        std::cout << "Failed to load sound_button image " << std::endl;
        success = false;
    }
    else
    {
        for(int i =0 ;i < BUTTON_TOTAL; i++)
        {
            gSoundButton[i].x = 34*i;
            gSoundButton[i].y = 0;
            gSoundButton[i].w = 34;
            gSoundButton[i].h = 32;
        }
    }

    for (int i = 0; i < LAYERS; i++)
    {
        if (!(gBackground[i].LoadFromFile(LAYER[i], gRenderer)))
            success = false;
    }
    if (!(gBlood.LoadFromFile("imgs/blood/blood.png", gRenderer)))
    {
        std::cout << "Can't load character image" << SDL_GetError() << std::endl;
        success = false;
    }
    // Init Music
    gMusic = Mix_LoadMUS("sound/musicloop.wav");
    if (gMusic == nullptr)
    {
        std::cout << "Unable to load background audio " << Mix_GetError() << std::endl;
        success = false;
    }

    gMenuMusic = Mix_LoadMUS("sound/musicloop.wav");
    if (gMenuMusic == nullptr)
    {
        std::cout << "Unable to load menu audio " << Mix_GetError() << std::endl;
        success = false;
    }

    gMouseClick = Mix_LoadWAV("sound/click.wav");
    if (gMouseClick == nullptr)
    {
        std::cout << "Unable to load mouse click " << Mix_GetError() << std::endl;
        success = false;
    }

    gLose = Mix_LoadWAV("sound/hurt.wav");
    if (gLose == nullptr)
    {
        std::cout << "Unable to load lose sound " << Mix_GetError() << std::endl;
        success = false;
    }

    gJump = Mix_LoadWAV("sound/jump.wav");
    if (gJump == nullptr)
    {
        std::cout << "Unable to load jump sound " << Mix_GetError() << std::endl;
        success = false;
    }
    gEat = Mix_LoadWAV("sound/eatCarrot.wav");
    if (gEat == nullptr)
    {
        std::cout << "Unable to load jump sound " << Mix_GetError() << std::endl;
        success = false;
    }
    // Init Character
    if (!(gCharacterTexture.LoadFromFile("imgs/character/jump.png", gRenderer)))
    {
        std::cout << "Can't load character image" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < CHA_LAYERS; i++)
        {
            gCharacterClips[i].x = 64 * i;
            gCharacterClips[i].y = 0;
            gCharacterClips[i].w = 64;
            gCharacterClips[i].h = 55;
        }
    }
    if (!(gStatusTexture.LoadFromFile("imgs/status/hurt.png", gRenderer)))
    {
        std::cout << "Can't load character image" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            gStatusHurt[i].x = 37 * i;
            gStatusHurt[i].y = 0;
            gStatusHurt[i].w = 37;
            gStatusHurt[i].h = 32;
        }
    }
    if(!(gStatusNormalTexture.LoadFromFile("imgs/status/idle.png",gRenderer)))
    {
        std::cout << "Can't load character image" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        for(int i = 0; i< 9; i++)
        {
            gStatusNormal[i].x = 37 * i;
            gStatusNormal[i].y = 0;
            gStatusNormal[i].w = 37;
            gStatusNormal[i].h = 32;
        }
    }

    return success;
}
void close()
{
    gMenuTexture.Free();
    gInstructionTexture.Free();
    gCharacterTexture.Free();
    gPlayButtonTexture.Free();
    gHelpButtonTexture.Free();
    gExitButtonTexture.Free();
    gBackButtonTexture.Free();
    gPauseButtonTexture.Free();
    gContinueButtonTexture.Free();
    gLoseTexture.Free();
    gYourScoreTexture.Free();
    gHighestScoreTexture.Free();
    gHighScore.Free();
    gScore.Free();

    for (int i = 0; i < LAYERS; ++i)
    {
        gBackground[i].Free();
    }

    Mix_FreeMusic(gMusic);
    Mix_FreeMusic(gMenuMusic);
    Mix_FreeChunk(gClick);
    Mix_FreeChunk(gLose);
    Mix_FreeChunk(gJump);
    gMusic = nullptr;
    gMenuMusic = nullptr;
    gClick = nullptr;
    gLose = nullptr;
    gJump = nullptr;
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}