#include "Minion.h"
#include "Bullet.h"
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
	double speed = PI / 80;
	double centerX = center->box->x;
	double centerY = center->box->y;

	Vec2 *pos = new Vec2(centerX, centerY);
	pos = pos->translate(200, 0);
	pos = pos->rotate(arc, centerX, centerY);

	box->x = pos->x;
	box->y = pos->y;

	arc += speed;
}

void Minion::Render(){
	sp->Render(box->GetDrawX() + Camera::pos[0].x, box->GetDrawY() + Camera::pos[0].y);	
}

bool Minion::IsDead(){
	return false;
}

void Minion::Shoot(Vec2 pos){
	double angle = Vec2::angle(pos.x - box->x, pos.y - box->y);

	Bullet *bullet = new Bullet(box->x, box->y, angle, 100, 1000, "img/minionbullet1.png");

	Game::GetInstance()->GetState()->AddObject(bullet);
}