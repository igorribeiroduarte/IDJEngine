#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Animation.h"
#include "Penguins.h"

#include <cmath>

Alien::Alien(double x, double y, int nMinions){
	sp = new Sprite("img/alien.png");
	box = Rect(x, y, sp->GetWidth(), sp->GetHeight());
	speed = Vec2(0, 0);
	hp = 30;
	alienCount++;
	state = Alien::AlienState::RESTING;

	double arc = 0;
	for(int i = 0; i < nMinions; i++){
		double PI = acos(-1);
		arc += 2 * PI / nMinions;
		minionArray.emplace_back(new Minion(this, arc));
	}

	countActiveMoveActions = 0;
}

Alien::~Alien(){
	alienCount--;
}

void Alien::Update(double dt){
	for(auto &it : minionArray)
		it->Update();

	rotation -= 15 * dt;
	rotation = fmod(rotation + 360, 360);

	printf("%f\n", restTimer.Get());

	if(Penguins::player){
		if(restTimer.Get() > 5){
			destination.x = Penguins::player->box.x;
			destination.y = Penguins::player->box.y;

			double angle = Vec2::angle(destination.x - box.x, destination.y -  box.y);
			double speedModule = 100;

			speed.x = cos(angle) * dt * speedModule;
			speed.y = sin(angle) * dt * speedModule;

			state = Alien::AlienState::MOVING;
		}

		if(state == Alien::AlienState::RESTING){
			restTimer.Update(dt);
		}else if(state == Alien::AlienState::MOVING){
			state = Alien::AlienState::RESTING;

			box.x += speed.x;
			box.y += speed.y;

			double dist = hypot(box.x - destination.x, box.y - destination.y);

			if(dist <= 1000){
				restTimer.Restart();

				int idx = 0;
				double minDistance = hypot(minionArray[0]->box.x - destination.x, minionArray[0]->box.y - destination.y);
				for(int it = 0; it < (int)minionArray.size(); it++){
					double distance = hypot(minionArray[it]->box.x - destination.x, minionArray[it]->box.y - destination.y);

					if(distance < minDistance){
						minDistance = distance;
						idx = it;
					}
				}

				minionArray[idx]->Shoot(destination);	
			}
		}
	}
}

void Alien::Render(){
	sp->Render(box.GetDrawX() + Camera::pos[0].x, box.GetDrawY() + Camera::pos[0].y, rotation);	

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
				Animation *animation = new Animation(box.x, box.y, rotation, "img/aliendeath.png", 4, 1, 4, true);			
				Game::GetInstance()->GetState()->AddObject(animation);
			}
		}
	}
}

bool Alien::Is(std::string type){
	return (type == "alien");
}
