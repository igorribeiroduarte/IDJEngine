#include "InputManager.h"
#include "Camera.h"

#include <SDL2/SDL.h>
#include <cstring>

InputManager::InputManager(){
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;

	memset(mouseState, false, sizeof mouseState);
	memset(mouseUpdate, 0, sizeof mouseUpdate);
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

	mouseX -= Camera::pos[0].x;
	mouseY -= Camera::pos[0].y;

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

int InputManager::GetMouseX(){
	return mouseX;
}

int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}

bool InputManager::IsKeyDown(int key){
	return keyState[key];
}

bool InputManager::KeyRelease(int key){
	return ((keyUpdate[key] == updateCounter) and (not IsKeyDown(key)));
}

bool InputManager::KeyPress(int key){
	return ((keyUpdate[key] == updateCounter) and (IsKeyDown(key)));
}

bool InputManager::IsMouseDown(int button){
	return mouseState[button]; 
}

bool InputManager::MouseRelease(int button){
	return ((mouseUpdate[button] == updateCounter) and (not IsMouseDown(button)));
}

bool InputManager::MousePress(int button){
	return ((mouseUpdate[button] == updateCounter) and (IsMouseDown(button)));
}

