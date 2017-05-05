#ifndef STATE_H
#define STATE_H

#include "SDL2/SDL.h"
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"

#include <memory>
#include <vector>

class Sprite;

class State{
	public:
		State();
		~State();

		bool QuitRequested();

		void LoadAssets();
		void Update(double dt);
		void Render();
		void Input();
		void AddObject(GameObject *ptr);

	private:
		Sprite *bg;

		TileMap *tileMap;
		TileSet *tileSet;

		bool quitRequested;

		std::vector < std::unique_ptr <GameObject> > objectArray;

		static State *instance;
};

#endif
