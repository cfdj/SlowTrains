#include <SDL.H>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "ParallaxLayer.h"
#include "ParticleSystem.h"
#include "UI.h"
#include "SoundPlayer.h"
#include "Loader.h"
#include "GameManager.h"

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 128;
//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;
SDL_Renderer* globalRenderer = NULL;

//Game loader
Loader loader = NULL;


void End() {
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    // Destroy Renderer
    SDL_DestroyRenderer(globalRenderer);
    globalRenderer = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void init() {
    IMG_Init(IMG_INIT_PNG);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Slow Trains", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        globalRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (globalRenderer == NULL)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        SDL_RenderSetLogicalSize(globalRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        //Load from csvs
        loader = Loader(globalRenderer);
    }

}
int main(int argc, char* args[])
{
    init();
    //Temporay loading sequence for testing
    std::string backgroundpath = "Sprites/Locations/Background.png";
    std::string cloudspath = "Sprites/Locations/Clouds.png";
    std::string hillspath = "Sprites/Locations/Hills1.png";
    std::string hillspath2 = "Sprites/Locations/Island.png";
    std::string closepath = "Sprites/Locations/Fence.png";
    std::string railspath = "Sprites/Locations/Rails.png";
    std::string foregroundPath = "Sprites/Locations/RedRocks.png";
    //std::string trainpath = "Sprites/Trains/Swan.png";
    std::string carrigepath = "Sprites/Trains/Carrige.png";

    //UI paths;
    std::string speedSlowPath = "Sprites/UI/speedControlSlow.png";
    std::string speedMediumPath = "Sprites/UI/speedControlMedium.png";
    std::string speedFullPath = "Sprites/UI/speedControlFast.png";
    int trainNum = 0;
    int pos = 0;
    int posX = 40;
    int posY = 92;
    int speed = 5;
    float backgroundSpeed = 0;
    float cloudSpeed = 0.2;
    float hillsSpeed = 0.2;
    float closeSpeed = 0.4;
    float railsSpeed = 0;
    float foregroundSpeed = 0.4;

    Sprite backgroundSprite = Sprite(backgroundpath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite cloudSprite = Sprite(cloudspath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite hillSprite = Sprite(hillspath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite hillSprite2 = Sprite(hillspath2, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite closeSprite = Sprite(closepath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite railsSprite = Sprite(railspath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite foregroundSprite = Sprite(foregroundPath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
//    AnimatedSprite trainSprite = AnimatedSprite(trainpath, width, height, 4, 1, globalRenderer);
    Sprite Carrige = Sprite(carrigepath, 73, 24, 0, 0, globalRenderer); //Should share size with the Trains for consistency
    ParallaxLayer background = ParallaxLayer(backgroundSpeed, &backgroundSprite);
    ParallaxLayer clouds = ParallaxLayer(cloudSpeed, &cloudSprite);
    ParallaxLayer hills = ParallaxLayer(hillsSpeed, &hillSprite);
    ParallaxLayer close = ParallaxLayer(closeSpeed, &closeSprite);
    ParallaxLayer rails = ParallaxLayer(railsSpeed, &railsSprite);
    ParallaxLayer foreground = ParallaxLayer(foregroundSpeed, &foregroundSprite);

    int xMove = -2;
    int yMove = -1;
    int funnelX = loader.getFunnelX(trainNum); //This probably needs to adjust based not only on train, but also on number of carriges
    int funnelY = loader.getFunnelY(trainNum);

    ParticleSystem steam = ParticleSystem("Sprites/steam.png",funnelX,funnelY,xMove,yMove,8,8,5,1,globalRenderer); //This positioning needs some way to track with the funnel position
    
    //UI
    Sprite speedSlow = Sprite(speedSlowPath, 64, 64, 0, 0, globalRenderer);
    Sprite speedMedium = Sprite(speedMediumPath, 64, 64, 0, 0, globalRenderer);
    Sprite speedFull = Sprite(speedFullPath, 64, 64, 0, 0, globalRenderer);
    UI speedDisplay = UI(&speedSlow, &speedMedium, &speedFull, SCREEN_WIDTH - 64, SCREEN_HEIGHT - 64);

    //Sound
    SoundPlayer soundPlayer = SoundPlayer();
    //Main loop flag
    bool quit = false;

    //GameManager Starting
    GameManager gameManager = GameManager(&speedDisplay,&background, &soundPlayer,&loader,&steam);

    //AnimatedSprite trainSprite = gameManager.getTrain();
    AnimatedSprite trainSprite = loader.getTrain(1);
    //Event handler
    SDL_Event e;

    //While application is running
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else 
            {
                gameManager.handleInput(e);
                //trainSprite = gameManager.getTrain();
            }
                
        }
        
        //Rendering the frame
        SDL_RenderClear(globalRenderer);
        background.render();
        clouds.render();
        hills.render();
        close.render();
        rails.render();
        steam.render();
        Carrige.render(-19,96);
        trainSprite.render(posX,posY); //The order matters
        foreground.render();
        speedDisplay.render();
        SDL_RenderPresent(globalRenderer);
    }
    End();
    return 0;
}