#ifndef STATE_H
#define STATE_H

#include "SDL2/SDL.h"

class State{
	public:
		State();

		bool QuitRequested();

		void LoadAssets();
		void Update();
		void Render();

	private:
		Sprite bg;

		bool quitRequested;
};

#endif
