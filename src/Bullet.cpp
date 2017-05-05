#include "Bullet.h"
#include "Camera.h"

#include <cmath>

Bullet::Bullet(double x, double y, double angle, double speedModule, double maxDistance, std::string sprite){
	sp = new Sprite(sprite);
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());

	speed.x = cos(angle) * speedModule;
	speed.y = sin(angle) * speedModule;

	distanceLeft = maxDistance;
}

void Bullet::Update(double dt){
	box->x += speed.x * dt;
	box->y += speed.y * dt;

	distanceLeft -= speed.x * dt;	
}

void Bullet::Render(){
	sp->Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y);	
}

bool Bullet::IsDead(){
	return distanceLeft <= 0;
}
