#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "State.h"

#include <string>
#include <stack>
#include <memory>

using namespace std;

class Game{
	public:
		Game(string title, int width, int height);

		~Game();

		void Run();

		void Push(State *state);

		static Game *GetInstance();

		double GetDeltaTime();

		SDL_Renderer *GetRenderer();

		State *GetCurrentState();
		
	private:
		void CalculateDeltaTime();

		static Game *instance;

		SDL_Window *window;

		SDL_Renderer *renderer;

		State *storedState;

		int frameStart;

		stack < unique_ptr <State> > stateStack;

		double dt;
};

#endif
