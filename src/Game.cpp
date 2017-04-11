#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height){
	if(instance != nullptr){
		printf("Existe um problema com a lógica do jogo. Há mais de uma instância de Game em execução\n");
		exit(1);
	}else
		instance = this;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
		printf("Falha ao executar a função SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	int flags_img_init = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if(IMG_Init(flags_img_init) != flags_img_init){
		printf("Falha ao inicializar o suporte a imagens no jogo: %s\n", IMG_GetError());
		exit(1);
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if(window == nullptr){
		printf("Falha ao criar janela: %s\n", SDL_GetError());
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(renderer == nullptr){
		printf("Falha ao criar renderizador: %s\n", SDL_GetError());
		exit(1);
	}

	srand(time(NULL));

	state = new State();

	frameStart = 0;
	dt = 0;
}

Game::~Game(){
	delete(state);

	IMG_Quit();

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	
	SDL_Quit();
}

Game *Game::GetInstance(){
	return instance;
}

State *Game::GetState(){
	return state;
}

SDL_Renderer *Game::GetRenderer(){
	return renderer;
}

void Game::Run(){
	state->LoadAssets();

	while(not state->QuitRequested()){
		state->Update(dt);
		state->Render();

		SDL_RenderPresent(renderer);

		SDL_Delay(33);
	}

	Resources::ClearImages();
}

void Game::CalculateDeltaTime(){
	int frameEnd = SDL_GetTicks();

	dt = (frameEnd - frameStart) / 1000.0;

	frameStart = frameEnd;
}

double Game::GetDeltaTime(){
	return dt;
}
