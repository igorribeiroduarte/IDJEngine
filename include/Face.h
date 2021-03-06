#ifndef FACE_H
#define FACE_H

#include "GameObject.h"
#include "Sprite.h"

class Face : public GameObject{
	public:
		Face(double x, double y);
		~Face();

		void Damage(int damage);
		void Update(double dt);
		void Render();

		bool IsDead();

	private:
		int hitpoints;

		Sprite *sp;
};

#endif
