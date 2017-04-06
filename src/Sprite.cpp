#include "Sprite.h"
#include "Game.h"
#include "Resources.h" 

Sprite::Sprite(){
	texture = nullptr;
}

Sprite::Sprite(string file){
	texture = nullptr;
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

void Sprite::Render(int x, int y){
	dstRect = new SDL_Rect{ x, y, clipRect->w, clipRect->h };
	SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, clipRect, dstRect);
}

int Sprite::GetWidth(){
	return width;
}

int Sprite::GetHeight(){
	return height;
}

bool Sprite::IsOpen(){
	if(texture != nullptr)
		return true;
	else
		return false;
}
