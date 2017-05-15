#include "Bullet.h"
#include "Camera.h"

#include <cmath>

Bullet::Bullet(double x, double y, double angle, double pSpeedModule, double maxDistance, std::string sprite, int frameCount, double frameTime, bool pTargetsPlayer){
	sp = new Sprite(sprite, frameCount, frameTime);
	sp->SetScaleX(2);
	sp->SetScaleY(2);
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());

	speedModule = pSpeedModule;

	speed.x = cos(angle) * speedModule;
	speed.y = sin(angle) * speedModule;

	distanceLeft = maxDistance;

	rotation = (angle * 180) / acos(-1);

	targetsPlayer = pTargetsPlayer;
}

Bullet::~Bullet(){
	delete(sp);
	delete(box);
}

void Bullet::Update(double dt){
	sp->Update(dt);

	box->x += speed.x * dt;
	box->y += speed.y * dt;

	distanceLeft -= speedModule * dt;	
}

void Bullet::Render(){
	sp->Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y, rotation);	
}

bool Bullet::IsDead(){
	return distanceLeft <= 0;
}

void Bullet::NotifyCollision(GameObject &other){
	if(!other.Is("bullet")){
		if(targetsPlayer == !other.Is("alien"))
			distanceLeft = -1;
	}
}

bool Bullet::Is(std::string type){
	return (type == "bullet");
}
