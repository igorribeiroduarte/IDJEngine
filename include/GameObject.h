#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"

class GameObject{
	public:
		Rect *box;

		virtual ~GameObject(){}

		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
		
		virtual bool IsDead() = 0;
};

#endif
