#ifndef ANIMATION_H
#define ANIMATION_H

#include "GameObject.h"
#include "Timer.h"
#include "Sprite.h"

#include <string>

class Animation : public GameObject{
	public:
		Animation(double x, double y, double rotation, std::string sprite, int frameCount, double frameTime, double pTimeLimit, bool ends);

		void Update(double dt);
		void Render();
		void NotifyCollision(GameObject &other);

		bool IsDead();
		bool Is(std::string type);
	
	private:
		Timer endTimer;
		double timeLimit;
		bool oneTimeOnly;
		Sprite *sp;
};

#endif
