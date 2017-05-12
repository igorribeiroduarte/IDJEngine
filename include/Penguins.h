#ifndef PENGUINS_H
#define PENGUINS_H

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Penguins : public GameObject{
	public:
		Penguins(double x, double y);
		~Penguins();

		void Update(double dt);
		void Render();
		void Shoot();

		bool IsDead();

		static Penguins *player;

	private:
		Sprite bodySp, cannonSp;

		Vec2 *speed;

		double linearSpeed, cannonAngle;

		int hp;
};

#endif
