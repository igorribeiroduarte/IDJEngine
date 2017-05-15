#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"

#include <string>

class GameObject{
	public:
		Rect *box;

		double rotation;

		GameObject(){ rotation = 0; }
		virtual ~GameObject(){}

		virtual void Update(double dt) = 0;
		virtual void Render() = 0;
		virtual void NotifyCollision(GameObject &other) = 0;

		virtual bool IsDead() = 0;
		virtual bool Is(std::string type) = 0;
};

#endif
