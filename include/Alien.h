#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"
#include "Sprite.h"
#include "Minion.h"
#include "Vec2.h"
#include "Timer.h"

#include <memory>
#include <vector>
#include <queue>

class Alien : public GameObject{
	public:
		static int alienCount;

		Alien(double x, double y, int nMinions);
		~Alien();

		void Update(double dt);
		void Render();
		void NotifyCollision(GameObject &other);

		bool IsDead();
		bool Is(std::string type);

	private:
		enum AlienState {MOVING, RESTING};
		
		AlienState state;

		Timer restTimer;

		Vec2 destination;

		Sprite *sp;

		Vec2 speed;

		int hp;

		int countActiveMoveActions;

		std::vector < std::unique_ptr <Minion> > minionArray;
};

#endif
