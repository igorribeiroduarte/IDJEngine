#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "State.h"

#include <string>

using namespace std;

class Game{
	public:
		Game(string title, int width, int height);

		~Game();

		void Run();

		static Game *GetInstance();

		double GetDeltaTime();

		State *GetState();

		SDL_Renderer *GetRenderer();
		
	private:
		void CalculateDeltaTime();

		static Game *instance;

		SDL_Window *window;

		SDL_Renderer *renderer;

		State *state;

		int frameStart;

		double dt;
};

#endif
