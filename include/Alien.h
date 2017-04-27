#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

#include <queue>
#include <vector>

class Alien : public GameObject{
	public:
		Alien(double x, double y, int nMinions);
		~Alien();

		void Update(double dt);
		void Render();

		bool IsDead();

	private:
		class Action{
			public:
				enum ActionType {MOVE, SHOOT};

				Action(ActionType pType, double x, double y){
					type = pType;
					pos = Vec2(x, y);
				}

				ActionType type;

				Vec2 pos;
		};

		Sprite sp;

		Vec2 speed;

		int hp;

		std::queue <Action> taskQueue;
		std::vector <Minion> minionArray;
};

#endif
