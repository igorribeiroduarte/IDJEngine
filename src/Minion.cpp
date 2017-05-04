#include "Minion.h"

#include <cmath>

Minion::Minion(GameObject *minionCenter, double arcOffSet){
//	sp = new Sprite("img/minion.png");
//	center = minionCenter;
//	arc = arcOffSet;
	//calc box value
}

void Minion::Update(double){
/*	const double PI = acos(-1);
	double speed = PI / 6;
	double centerX = center->box->x;
	double centerY = center->box->y;

	Vec2 pos = Vec2(centerX, centerY);
	pos.translate(200, 0);
	pos.rotate(arc, centerX, centerY);

	box->x = pos.x;
	box->y = pos.y;

	arc += speed;*/
}

void Minion::Render(){
//	sp->Render(box->x, box->y);
}

bool Minion::IsDead(){
	return false;
}
