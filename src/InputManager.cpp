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
			printf("%d\n", (int)event.button.button);
			mouseState[event.button.button] = true;
			printf("%d\n", (int)IsMouseDown(event.button.button));
			mouseUpdate[event.button.button] = updateCounter;
		}

		//Botão do mouse foi solto
		if(event.type == SDL_MOUSEBUTTONUP){
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
			printf("%d\n", (int)IsMouseDown(event.button.button));
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
//	return true;
	if(mouseState[button]){
		printf("AJFPEAIFJAIJEAIJP\n");
		return true;
	}else
		return false;

	//return true;
	printf("mouseState[%d]=%d\n", button, (int)mouseState[button]);
	return mouseState[button] == true; 
}

bool InputManager::MouseRelease(int button){
	if(updateCounter==0) return false;
	return ((mouseUpdate[button] == updateCounter) and (not IsMouseDown(button)));
}

bool InputManager::MousePress(int button){
	return ((mouseUpdate[button] == updateCounter) and (IsMouseDown(button)));
}

