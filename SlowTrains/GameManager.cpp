#include "GameManager.h"

GameManager::GameManager(UI* _ui, ParallaxLayer* _parallax, SoundPlayer* _soundPlayer)
{
}

GameManager::~GameManager()
{
}

void GameManager::handleInput(SDL_Event e) //Currently doesn't handle Quiting, as that is tied to main
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    //User requests quit
    if (keyboardState[start]) {
        if (state != Running) {
            state = Running;
            parallax->SetSpeed(speed);
            //steam.playing = true;
            //trainSprite.playing = true;
            ui->setState(1);
            soundPlayer->setSpeed(1);
            soundPlayer->startMusic();
        }
        //For sound testing
        else if (state == Running) {
            soundPlayer->playWhistle();
        }
}
