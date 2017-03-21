#include "State.h"

#include "Sprite.h"

State::State(){
	quitRequested = false;
	bg = new Sprite();
}

State::~State(){
	delete(bg);
}

void State::LoadAssets(){
	bg->Open("res/img/ocean.jpg");
}

void State::Update(){
	quitRequested = SDL_QuitRequested();	
}

void State::Render(){
	bg->Render(0, 0);
}

bool State::QuitRequested(){
	return quitRequested;
}
