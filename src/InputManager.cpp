#include "InputManager.h"

#include <SDL2/SDL.h>

InputManager::InputManager(){
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
}

InputManager::~InputManager(){
	keyState.clear();
	keyUpdate.clear();
}

InputManager &InputManager::GetInstance(){
	static InputManager instance;

	return instance;
}

void InputManager::Update(){
	SDL_Event event;

	//Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	quitRequested = false;

	updateCounter++;

	//SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while(SDL_PollEvent(&event)){

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT){
			quitRequested = true;
		}

		//Pressionamento de tecla
		if(event.type == SDL_KEYDOWN && not event.key.repeat){
			keyState[event.key.keysym.sym] = true;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}

		//Tecla foi solta
		if(event.type == SDL_KEYUP){
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}

		//Clique
		if(event.type == SDL_MOUSEBUTTONDOWN){	
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}

		//Botão do mouse foi solto
		if(event.type == SDL_MOUSEBUTTONUP){
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}
	}
}

bool InputManager::KeyRelease(int key){

}

int InputManager::GetMouseX(){
	return mouseX;
}

int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}

bool InputManager::KeyPress(int key){
	return true;	
}
