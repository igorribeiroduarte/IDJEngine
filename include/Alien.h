#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"
#include "Sprite.h"
#include "Minion.h"
#include "Vec2.h"

#include <memory>
#include <vector>
#include <queue>

class Alien : public GameObject{
	public:
		Alien(double x, double y, int nMinions);
		~Alien();

		void Update(double dt);
		void Render();
		void NotifyCollision(GameObject &other);

		bool IsDead();
		bool Is(std::string type);

	private:
		class Action{
			public:
				enum ActionType {MOVE, SHOOT};

				Action(ActionType pType, Vec2 pFinalPos){
					type = pType;
					finalPos = pFinalPos;
				}

				ActionType type;

				Vec2 finalPos;
		};

		Sprite *sp;

		Vec2 speed;

		int hp;

		int countActiveMoveActions;

		std::queue <Action> taskQueue;
		std::vector < std::unique_ptr <Minion> > minionArray;
};

#endif
