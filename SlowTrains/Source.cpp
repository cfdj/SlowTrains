#include <SDL.H>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "ParallaxLayer.h"
#include "ParticleSystem.h"
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 128;
//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;
SDL_Renderer* globalRenderer = NULL;

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
    }

}
int main(int argc, char* args[])
{
    init();
    //Temporay loading sequence for testing
    std::string backgroundpath = "Sprites/Background.png";
    std::string cloudspath = "Sprites/Clouds.png";
    std::string hillspath = "Sprites/Hills.png";
    std::string closepath = "Sprites/Close.png";
    std::string railspath = "Sprites/Rails.png";
    std::string foregroundPath = "Sprites/Foreground.png";
    std::string trainpath = "Sprites/Trains/WestCoaster.png";
    std::string carrigepath = "Sprites/Trains/Carrige.png";
    int width = 82;
    int height = 28;
    int pos = 0;
    int posX = 40;
    int posY = 92;
    float backgroundSpeed = 0;
    float cloudSpeed = 0.2;
    float hillsSpeed = 0.2;
    float closeSpeed = 0.4;
    float railsSpeed = 0;
    float foregroundSpeed = 0.4;
    Sprite backgroundSprite = Sprite(backgroundpath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite cloudSprite = Sprite(cloudspath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite hillSprite = Sprite(hillspath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite closeSprite = Sprite(closepath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite railsSprite = Sprite(railspath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    Sprite foregroundSprite = Sprite(foregroundPath, SCREEN_WIDTH, SCREEN_HEIGHT, pos, pos, globalRenderer);
    AnimatedSprite trainSprite = AnimatedSprite(trainpath, width, height, 4, 1, globalRenderer);
    Sprite Carrige = Sprite(carrigepath, 73, 24, 0, 0, globalRenderer);
    ParallaxLayer background = ParallaxLayer(backgroundSpeed, &backgroundSprite);
    ParallaxLayer clouds = ParallaxLayer(cloudSpeed, &cloudSprite);
    ParallaxLayer hills = ParallaxLayer(hillsSpeed, &hillSprite);
    ParallaxLayer close = ParallaxLayer(closeSpeed, &closeSprite);
    ParallaxLayer rails = ParallaxLayer(railsSpeed, &railsSprite);
    ParallaxLayer foreground = ParallaxLayer(foregroundSpeed, &foregroundSprite);

    int xMove = -2;
    int yMove = -1;
    ParticleSystem steam = ParticleSystem("Sprites/steam.png",108,88,xMove,yMove,8,8,5,1,globalRenderer);
    //Main loop flag
    bool quit = false;

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
        SDL_RenderPresent(globalRenderer);
    }
    End();
    return 0;
}