#include "Sprite.h"
#include "Game.h"
#include "Resources.h" 

Sprite::Sprite(){
	texture = nullptr;

	scaleX = scaleY = 1;
}

Sprite::Sprite(string file){
	texture = nullptr;

	scaleX = scaleY = 1;

	Open(file);
}

Sprite::~Sprite(){
	delete(clipRect);
	delete(dstRect);
}

void Sprite::Open(string file){
	texture = Resources::GetImage(file);

	if(not IsOpen()){
		printf("Falha ao carregar a imagem: %s\n", SDL_GetError());
		exit(1);
	}

	if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0){
		printf("Falha ao pegar as dimensões da imagem: %s\n", SDL_GetError());
		exit(1);
	}

	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect = new SDL_Rect { x, y, w, h };
}

void Sprite::Render(int x, int y, double angle){
	dstRect = new SDL_Rect{ x, y, clipRect->w * scaleX, clipRect->h * scaleY};
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, clipRect, dstRect, angle, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth(){
	return width * scaleX;
}

int Sprite::GetHeight(){
	return height * scaleY;
}

void Sprite::SetScaleX(int scale){
	scaleX = scale;
}

void Sprite::SetScaleY(int scale){
	scaleY = scale;
}

bool Sprite::IsOpen(){
	if(texture != nullptr)
		return true;
	else
		return false;
}
