#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Animation.h"

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

	countActiveMoveActions = 0;
}

Alien::~Alien(){
	delete(box);
}

void Alien::Update(double dt){
	for(auto &it : minionArray)
		it->Update();
	
	rotation -= 15*dt;
	rotation = fmod(rotation + 360, 360);

	InputManager &inputManager = InputManager::GetInstance();

	double mouseX = inputManager.GetMouseX();
	double mouseY = inputManager.GetMouseY();

	if(inputManager.MousePress(InputManager::LEFT_MOUSE_BUTTON)){
		Action action = Action(Action::ActionType::SHOOT, Vec2(mouseX, mouseY));
		taskQueue.emplace(action);
	}else if(inputManager.MousePress(InputManager::RIGHT_MOUSE_BUTTON)){
		Action action = Action(Action::ActionType::MOVE, Vec2(mouseX, mouseY));
		taskQueue.emplace(action);
		countActiveMoveActions++;
	}

	if(not taskQueue.empty()){
		Action action = taskQueue.front();

		if(action.type == Action::ActionType::SHOOT){
			int minionIdx = rand() % minionArray.size();

			int idx = 0;
			double minDistance = hypot(minionArray[0]->box->x - action.finalPos.x, minionArray[0]->box->y - action.finalPos.y);
			for(int it = 0; it < (int)minionArray.size(); it++){
				double distance = hypot(minionArray[it]->box->x - action.finalPos.x, minionArray[it]->box->y - action.finalPos.y);

				if(distance < minDistance){
					minDistance = distance;
					idx = it;
				}
			}

			minionArray[idx]->Shoot(action.finalPos);

			taskQueue.pop();
		}else if(action.type == Action::ActionType::MOVE){
			if(countActiveMoveActions > 1){
				taskQueue.pop();
				countActiveMoveActions--;
			}

			double angle = Vec2::angle(action.finalPos.x - box->x, action.finalPos.y -  box->y);
			double speedModule = 500;

			speed.x = cos(angle) * dt * speedModule;
			speed.y = sin(angle) * dt * speedModule;

			const double EPS = 10;
			if(fabs(box->x - action.finalPos.x) >= EPS || fabs(box->y - action.finalPos.y) >= EPS){
				box->x += speed.x;
				box->y += speed.y;
			}else{
				taskQueue.pop();
				countActiveMoveActions--;
			}
		}
	}
}

void Alien::Render(){
	sp->Render(box->GetDrawX() + Camera::pos[0].x, box->GetDrawY() + Camera::pos[0].y, rotation);	

	for(auto &it : minionArray)
		it->Render();
}

bool Alien::IsDead(){
	if(hp <= 0)
		return true;
	else
		return false;
}

void Alien::NotifyCollision(GameObject &other){
	if(other.Is("bullet")){
		if(!((Bullet &)other).targetsPlayer){
			hp -= 5;
			
			if(IsDead()){
				Animation *animation = new Animation(box->x, box->y, rotation, "img/aliendeath.png", 4, 1, 4, true);			
				Game::GetInstance()->GetState()->AddObject(animation);
			}
		}
	}
}

bool Alien::Is(std::string type){
	return (type == "alien");
}
