#include "State.h"

State::State(){
	quitRequested = false;
	bg = new Sprite();
}

void State::LoadAssets(){
	
}

void State::Update(float dt){
	quitRequested = SDL_QuitRequested();	
}

void State::Render(){
	//Renderizar fundo(bg) de forma a preencher a tela //TODO	
}

bool State::QuitRequested(){
	return quitRequested;
}
