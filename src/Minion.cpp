#include "Minion.h"
#include "Camera.h"

#include <cmath>

Minion::Minion(GameObject *minionCenter, double arcOffSet){
	sp = new Sprite("img/minion.png");

	center = minionCenter;

	box = new Rect(center->box->x + center->box->width / 2 + 200, 
	center->box->y + center->box->height / 2, sp->GetWidth(), sp->GetHeight());

	arc = arcOffSet;
}

void Minion::Update(double){
	const double PI = acos(-1);
	double speed = PI / 30;
	double centerX = center->box->x + center->box->width / 2;
	double centerY = center->box->y + center->box->height / 2;

	Vec2 *pos = new Vec2(centerX, centerY);
	pos = pos->translate(200, 0);
	pos = pos->rotate(arc, centerX, centerY);

	box->x = pos->x - box->width / 2;
	box->y = pos->y - box->height / 2;

	arc += speed;
}

void Minion::Render(){
	sp->Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y);	
}

bool Minion::IsDead(){
	return false;
}
