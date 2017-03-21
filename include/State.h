#ifndef STATE_H
#define STATE_H

#include "SDL2/SDL.h"

class Sprite;

class State{
	public:
		State();
		~State();

		bool QuitRequested();

		void LoadAssets();
		void Update();
		void Render();

	private:
		Sprite *bg;

		bool quitRequested;
};

#endif
