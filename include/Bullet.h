#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Bullet : public GameObject{
	public:
		bool targetsPlayer;

		Bullet(double x, double y, double angle, double speedModule, double maxDistance, std::string sprite, int frameCount = 1, double frameTime = 1, bool pTargetsPlayer = false);
		~Bullet();

		void Update(double dt = 0);
		void Render();
		void NotifyCollision(GameObject &other);

		bool IsDead();
		bool Is(std::string type);

	private:
		Sprite *sp;

		Vec2 speed;

		double distanceLeft, speedModule;
};

#endif
