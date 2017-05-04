#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"

#include <cmath>

Alien::Alien(double x, double y, int nMinions){
	sp = new Sprite("img/alien.png");
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());
	speed = Vec2(0, 0);
	hp = 30;
	
	double arc = 0;
	for(int i = 0; i < nMinions; i++){
		double PI = acos(-1);
		arc += 2 * PI / nMinions;
		minionArray.emplace_back(new Minion(this, arc));
	}
}

Alien::~Alien(){
	delete(box);
}

void Alien::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();

	double mouseX = inputManager.GetMouseX();
	double mouseY = inputManager.GetMouseY();

	double cameraX = Camera::pos[0].x;
	double cameraY = Camera::pos[0].y;

	double newPosX = mouseX;
	double newPosY = mouseY;

	if(inputManager.MousePress(InputManager::LEFT_MOUSE_BUTTON)){
		Action action = Action(Action::ActionType::SHOOT, newPosX, newPosY);
		taskQueue.emplace(action);
	}else if(inputManager.MousePress(InputManager::RIGHT_MOUSE_BUTTON)){
		Action action = Action(Action::ActionType::MOVE, box->x, box->y);
		taskQueue.emplace(action);
	}

	Action action = taskQueue.front();

	if(action.type == Action::ActionType::SHOOT){
		//TODO	
	}else if(action.type == Action::ActionType::MOVE){
		double deltaT = 200;

		speed.x = fabs(action.pos.x - newPosX) / deltaT;
		speed.y = fabs(action.pos.y - newPosY) / deltaT;

		const double EPS = 1e-9;
		if(fabs(box->x-newPosX) >= EPS  && fabs(box->y-newPosY) >= EPS){
			if(newPosX > box->x)
				box->x += speed.x;
			else
				box->x -= speed.x;

			if(newPosY > box->y)
				box->y += speed.y;
			else
				box->y -= speed.y;
		}else
			taskQueue.pop();
	}
}

void Alien::Render(){
	sp->Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y);	

	for(auto &it : minionArray){
		it->Update();
		it->Render();
	}
}

bool Alien::IsDead(){
	if(hp <= 0)
		return true;
	else
		return false;
}
