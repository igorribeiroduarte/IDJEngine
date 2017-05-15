#include "Animation.h"
#include "Camera.h"

Animation::Animation(double x, double y, double pRotation, std::string sprite, int frameCount, double frameTime, double pTimeLimit, bool ends){
	sp = new Sprite(sprite, frameCount, frameTime);
	rotation = pRotation;
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());
	oneTimeOnly = ends;
	timeLimit = pTimeLimit;
	endTimer = Timer();
}

void Animation::Update(double dt){
	endTimer.Update(dt);
	sp->Update(dt);
}

void Animation::Render(){
	sp->Render(box->GetDrawX() + Camera::pos[0].x, box->GetDrawY() + Camera::pos[0].y, rotation);	
}

bool Animation::IsDead(){
	return (oneTimeOnly && endTimer.Get() > timeLimit);
}

void Animation::NotifyCollision(GameObject &){
	
}

bool Animation::Is(std::string type){
	return (type == "animation");
}
