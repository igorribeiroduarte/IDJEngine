#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

#include "Game.h"
#include "Vec2.h"
#include "GameObject.h"
#include "InputManager.h"

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 600

class Camera{
	public:
		static Vec2 pos[6], speed[6];

		static void Follow(GameObject *newFocus);
		static void Unfollow();
		static void Update(double dt);

	private:
		static GameObject *focus;
};

#endif
