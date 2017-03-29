#ifndef STATE_H
#define STATE_H

#include "SDL2/SDL.h"
#include "GameObject.h"

#include <memory>
#include <vector>

class Sprite;

class State{
	public:
		State();
		~State();

		bool QuitRequested();

		void LoadAssets();
		void Update();
		void Render();
		void Input();
		void AddObject(double mouseX, double mouseY);

	private:
		Sprite *bg;

		bool quitRequested;

		std::vector < std::unique_ptr <GameObject> > objectArray;
};

#endif
