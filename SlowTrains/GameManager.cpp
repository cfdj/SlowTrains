#include "GameManager.h"

GameManager::GameManager(UI* _ui, ParallaxLayer* _parallax, SoundPlayer* _soundPlayer, Loader* _loader, ParticleSystem* _steam)
{
    ui = _ui;
    parallax = _parallax;
    soundPlayer = _soundPlayer;
    loader = _loader;
    train = _loader->getTrain(trainId);
    steam = _steam;
}

GameManager::~GameManager()
{
}
//Currently doesn't handle Quiting, as that is tied to main
void GameManager::handleInput(SDL_Event e) 
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    if (e.type == SDL_KEYDOWN) {
        //Player starts game
        switch (state)
            {
            case GameManager::Loading:
                break;
            case GameManager::InStation:
                //Player starts game
                if (keyboardState[start]) {
                    state = Running;
                    steam->setPlaying(true);
                    train->playing = true;
                    updateSpeed();
                    soundPlayer->startMusic();
                }
                if (keyboardState[nextTrain]) {
                    trainId += 1;
                    switchTrain();
                }
                if (keyboardState[previousTrain]) {
                    trainId -= 1;
                    switchTrain();
                }
                break;
            case GameManager::Running:
                if (keyboardState[start]) {
                    soundPlayer->playWhistle();
                }
                if (keyboardState[faster]) {
                    currentSpeed += 1;
                    if (currentSpeed > 2) {
                        currentSpeed = 2;
                    }
                    updateSpeed();

                }
                if (keyboardState[slower]) {
                    currentSpeed -= 1;
                    if (currentSpeed < 0) {
                        currentSpeed = 0;
                    }
                    updateSpeed();


                }
                break;
            default:
                break;
            }
    }
}

void GameManager::switchTrain()
{
    if (trainId < 0) {
        trainId = 0;
    } if (trainId > loader->getNumTrains() - 1) {
        trainId = loader->getNumTrains()-1;
    }

    train = loader->getTrain(trainId);
    steam->setXStart(loader->getFunnelX(trainId));
    steam->setYStart(loader->getFunnelY(trainId));
}

AnimatedSprite* GameManager::getTrain()
{
    return train;
}

void GameManager::render(int _xpos, int _ypos,SDL_Renderer* renderer)
{
    train->render(_xpos, _ypos, renderer);
}

void GameManager::updateSpeed()
{
    parallax->SetSpeed(speeds[currentSpeed]);
    ui->setState(currentSpeed);
    soundPlayer->setSpeed(currentSpeed);
    steam->setxMove(particleSpeeds[currentSpeed]);
}
