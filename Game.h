#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Game{
	public:
		Game(string title, int width, int height);
		~Game();

		void Run();

		Game &GetInstance();

		State &GetState();

		SDL_Renderer *GetRenderer();
		
	private:
		Game *instance;
		SDL_Window *window;
		SDL_Renderer *renderer;
		State *state;
};

#endif
