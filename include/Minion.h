#ifndef MINION_H
#define MINION_H

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Minion : public GameObject{
	public:
		Minion(GameObject *minionCenter, double arcOffset = 0);

		void Update(double dt = 0);
		void Render();
		void Shoot(Vec2 pos);
		
		bool IsDead();

	private:
		GameObject *center;
		
		Sprite *sp;

		double arc;
};

#endif
