#include "Face.h"
#include "InputManager.h"
#include "Camera.h"

Face::Face(double x, double y){
	sp = new Sprite("img/penguinface.png");
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());
	hitpoints = 30;
}

Face::~Face(){
	delete(sp);
	delete(box);
}

void Face::Damage(int damage){
	hitpoints -= damage;
}

void Face::Update(double){
	InputManager &inputManager = InputManager::GetInstance();

	for(int i = 0; i < 6; i++){
		if(inputManager.MousePress(i)){
			if(box->IsInside(inputManager.GetMouseX(), inputManager.GetMouseY())){
				Damage(rand() % 10 + 10);
			}
		}
	}
}

void Face::Render(){
	sp->Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y);
}

bool Face::IsDead(){
	if(hitpoints <= 0)
		return true;
	else
		return false;
}
