#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"

Alien::Alien(double x, double y, int nMinions){
	sp = Sprite("img/alien.png");
	box = new Rect(x, y, sp.GetWidth(), sp.GetHeight());
	speed = Vec2(0, 0);
	hp = 30;

	//Populate Array
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

	double newPosX = mouseX + cameraX;
	double newPosY = mouseY + cameraY;

	if(inputManager.MousePress(InputManager::LEFT_MOUSE_BUTTON)){
		Action action = Action(Action::ActionType::SHOOT, newPosX, newPosY);
		taskQueue.emplace(action);
	}else if(inputManager.MousePress(InputManager::RIGHT_MOUSE_BUTTON)){
		Action action = Action(Action::ActionType::MOVE, box->x, box->y);
		taskQueue.emplace(action);
	}

	while(not taskQueue.empty()){
		Action action = taskQueue.front();
		taskQueue.pop();

		if(action.type == Action::ActionType::SHOOT){
			//TODO	
		}else if(action.type == Action::ActionType::MOVE){
			double deltaT = 3.0;

			speed.x = fabs(action.pos.x - newPosX) / deltaT;
			speed.y = fabs(action.pos.y - newPosY) / deltaT;

			const double EPS = 1e-9;
			if((box->x-newPosX) >= EPS  && fabs(box->y-newPosY) >= EPS){
				box->x += speed.x;
				box->y += speed.y;
			}
		}
	}
}

void Alien::Render(){
	sp.Render(box->x + Camera::pos[0].x, box->y + Camera::pos[0].y);	
}

bool Alien::IsDead(){
	if(hp <= 0)
		return true;
	else
		return false;
}
