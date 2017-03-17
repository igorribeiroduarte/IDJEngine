#include "Sprite.h"

Sprite::Sprite(){
	texture = nullptr;
}

Sprite::Sprite(string file){
	texture = nullptr;
	Open(file);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(texture);
}

Sprite::Open(string file){
		
}
