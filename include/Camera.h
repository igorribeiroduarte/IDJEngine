#ifndef CAMERA_H
#define CAMERA_H

#include "Vec2.h"
#include "GameObject.h"

class Camera{
	public:
		static Vec2 pos, speed;

		static void Follow(GameObject *newFocus);
		static void Unfollow();
		static void Update(double dt);

	private:
		static GameObject *focus;
};

#endif
