#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

Game *Game::instance = nullptr;

Game::Game(string title, int width, int height){
	if(instance != nullptr){
		printf("Existe um problema com a lógica do jogo. Há mais de uma instância de Game em execução\n");
		exit(1);
	}else
		instance = this;

	int flags_img_init = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if(IMG_Init(flags_img_init) != flags_img_init){
		printf("Falha ao inicializar o suporte a imagens no jogo: %s\n", IMG_GetError());
		exit(1);
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
		printf("Falha ao executar a função SDL_Init: %s\n", SDL_GetError());
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
	
	if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_FLUIDSYNTH | MIX_INIT_MODPLUG) < 0){
		printf("Falha ao executar a função Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0){
		printf("Falha ao executar a função Mix_OpenAudio: %s\n", Mix_GetError());
		exit(1);
	}

	if(TTF_Init() == -1){
		printf("Falha ao executar a função TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}
	
	srand(time(NULL));

	storedState = nullptr;

	frameStart = 0;
	dt = 0;
}

Game::~Game(){
	if(storedState)
		delete(storedState);

	while(not stateStack.empty())
		stateStack.pop();

	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	SDL_Quit();
}

Game *Game::GetInstance(){
	return instance;
}

SDL_Renderer *Game::GetRenderer(){
	return renderer;
}

void Game::Run(){
	if(storedState){
		stateStack.emplace(storedState);
		storedState = nullptr;
	}else{
		printf("Estado inicial não encontrado\n");
		exit(1);
	}
	
	stateStack.top()->LoadAssets();

	while(not stateStack.empty()){
		if(stateStack.top()->QuitRequested()){
			while(not stateStack.empty())
				stateStack.pop();

			break;
		}

		CalculateDeltaTime();

		stateStack.top()->Update(dt);
		stateStack.top()->Render();

		SDL_RenderPresent(renderer);

		if(storedState){
			if(not stateStack.empty())
				stateStack.top()->Pause();

			stateStack.emplace(storedState);
			storedState = nullptr;

			stateStack.top()->LoadAssets();
		}

		SDL_Delay(33);
	}

//	Resources::ClearImages();
}

void Game::CalculateDeltaTime(){
	int frameEnd = SDL_GetTicks();

	dt = (frameEnd - frameStart) / 1000.0;

	frameStart = frameEnd;
}

double Game::GetDeltaTime(){
	return dt;
}

State *Game::GetCurrentState(){
	return stateStack.top().get();
}

void Game::Push(State *state){
	storedState = state;	
}
