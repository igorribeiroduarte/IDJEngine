#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "SDL2/SDL.h"
#include "GameObject.h"
#include "State.h"
#include "TileSet.h"
#include "TileMap.h"

#include <memory>
#include <vector>

class Sprite;

class StageState : public State{
	public:
		StageState();
		~StageState();

		void LoadAssets();

		void Update(double dt);
		void Render();

		void Pause();
		void Resume();

	private:
		Sprite *bg;

		TileMap *tileMap;
		TileSet *tileSet;
};

#endif
