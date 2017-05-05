#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Bullet : public GameObject{
	public:
		Bullet(double x, double y, double angle, double speedModule, double maxDistance, std::string sprite);

		void Update(double dt = 0);
		void Render();

		bool IsDead();

	private:
		Sprite *sp;

		Vec2 speed;

		double distanceLeft;
};

#endif
