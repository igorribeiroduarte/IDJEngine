#include "Bullet.h"
#include "Camera.h"

#include <cmath>

Bullet::Bullet(double x, double y, double angle, double speedModule, double maxDistance, std::string sprite, int frameCount, double frameTime){
	sp = new Sprite(sprite, frameCount, frameTime);
	sp->SetScaleX(2);
	sp->SetScaleY(2);
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());

	speed.x = cos(angle) * speedModule;
	speed.y = sin(angle) * speedModule;

	distanceLeft = maxDistance;

	rotation = (angle * 180) / acos(-1);
}

Bullet::~Bullet(){
	delete(sp);
	delete(box);
}

void Bullet::Update(double dt){
	sp->Update(dt);

	box->x += speed.x * dt;
	box->y += speed.y * dt;

	distanceLeft -= speed.x * dt;	
}

void Bullet::Render(){
	sp->Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y, rotation);	
}

bool Bullet::IsDead(){
	return distanceLeft <= 0;
}
