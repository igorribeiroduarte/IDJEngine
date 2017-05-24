#include "Sprite.h"
#include "Game.h"
#include "Resources.h" 

Sprite::Sprite(int pFrameCount, double pFrameTime){
	texture = nullptr;
	scaleX = scaleY = 1;
	timeElapsed = 0;
	currentFrame = 0;
	frameTime = pFrameTime;
	frameCount = pFrameCount;
}

Sprite::Sprite(string file, int pFrameCount, double pFrameTime){
	texture = nullptr;
	scaleX = scaleY = 1;
	timeElapsed = 0;
	currentFrame = 0;
	frameTime = pFrameTime;
	frameCount = pFrameCount;

	Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(string file){
	texture = Resources::GetImage(file);

	if(not IsOpen()){
		printf("Falha ao carregar a imagem: %s\n", SDL_GetError());
		exit(1);
	}

	if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) != 0){
		printf("Falha ao pegar as dimensões da imagem: %s\n", SDL_GetError());
		exit(1);
	}

	width /= frameCount;

	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect = new SDL_Rect { x, y, w, h };
}


void Sprite::Update(double dt){
	if(timeElapsed > frameTime){
		timeElapsed = 0;
		SetFrame((currentFrame + 1) % frameCount);
	}

	timeElapsed += dt;
}

void Sprite::SetFrame(int frame){
	currentFrame = frame;
	SetClip(currentFrame * width, clipRect->y, width, height);
}

void Sprite::SetFrameCount(int count){
	frameCount = count;
}

void Sprite::SetFrameTime(double time){
	frameTime = time;
}

void Sprite::Render(int x, int y, double angle){
	dstRect = new SDL_Rect{ x, y, clipRect->w * scaleX, clipRect->h * scaleY};
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture.get(), clipRect, dstRect, angle, nullptr, SDL_FLIP_NONE);
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
