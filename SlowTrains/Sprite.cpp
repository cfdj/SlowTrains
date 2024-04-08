#include "Sprite.h"

Sprite::Sprite(std::string _path, int _width, int _height, int _xOffset, int _yOffset, SDL_Renderer* _renderer)
{
	width = _width;
	height = _height;
	xOffset = _xOffset;
	yOffset = _yOffset;
	path = _path;
	rect = { width * xOffset,height * yOffset,width,height };
	renderer = _renderer;
	if (renderer == NULL) {
		printf("Error: Image not Loaded");
		printf(_path.c_str());
	}
	imageSurface = IMG_Load(_path.c_str());
	if (imageSurface == NULL) {
		printf("Error: Image not Loaded");
		printf(_path.c_str());
	}
	imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
}

Sprite::~Sprite()
{
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;
	SDL_DestroyTexture(imageTexture);
	imageTexture = NULL;
}

Sprite::Sprite(const Sprite &_other)
{

	width = _other.width;
	height = _other.height;
	xOffset = _other.xOffset;
	yOffset = _other.yOffset;
	path = _other.path;
	rect = _other.rect;
	renderer = _other.renderer;
	if (renderer == NULL) {
		printf("Error: renderer not present");
	}
	imageSurface = IMG_Load(path.c_str());
	if (imageSurface == NULL) {
		printf("Error: Image not Loaded");
		printf(_other.path.c_str());
	}
	imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	if (imageTexture == NULL) {
		printf("Error: Texture not made");
		printf(_other.path.c_str());
	}
}

void Sprite::render(int xPos, int yPos)
{
	SDL_Rect screenPos = { xPos,yPos,width,height };
	SDL_ClearError();
	int error = SDL_RenderCopy(renderer, imageTexture, &rect, &screenPos);
	if (error != 0) {
		printf("%d", error);
	}
}

Sprite::Sprite()
{
	width = 0;
	height = 0;
	xOffset = 0;
	yOffset = 0;
	rect = { width * xOffset,height * yOffset,width,height };
	renderer = NULL;
	imageSurface = NULL;
	imageTexture = NULL;
}
