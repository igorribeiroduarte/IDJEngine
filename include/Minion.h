#ifndef MINION_H
#define MINION_H

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

#include <string>

class Minion : public GameObject{
	public:
		Minion(GameObject *minionCenter, double arcOffset = 0);

		void Update(double dt = 0);
		void Render();
		void Shoot(Vec2 pos);
		void NotifyCollision(GameObject &other);
		
		bool IsDead();
		bool Is(std::string type);

	private:
		GameObject *center;
		
		Sprite *sp;

		double arc;
};

#endif
