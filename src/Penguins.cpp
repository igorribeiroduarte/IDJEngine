#include "Penguins.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Animation.h"

#include <cmath>

Penguins *Penguins::player;

Penguins::Penguins(double x, double y){
	bodySp = new Sprite("img/penguin.png");
	cannonSp = new Sprite("img/cubngun.png");
	speed = new Vec2(0, 0);
	cannonAngle = linearSpeed = 0;
	box = new Rect(x, y, bodySp->GetWidth(), bodySp->GetHeight());
	player = this;
	hp = 10; 
}

Penguins::~Penguins(){
	delete(bodySp);
	delete(cannonSp);
	delete(speed);
	player = nullptr;
}

void Penguins::Update(double dt){
	timer.Update(dt);

	InputManager &inputManager = InputManager::GetInstance();

	const double PI = acos(-1);
	const double aceleration = 80 * dt;
	const double maxSpeed = 800 * dt;
	const double angleSpeed = 130 * dt;

	cannonAngle = Vec2::angle(inputManager.GetMouseX() - box->x, inputManager.GetMouseY() - box->y) * 180 / PI; 

	if(inputManager.IsKeyDown(InputManager::W_KEY) && fabs(linearSpeed + aceleration) < maxSpeed)
		linearSpeed += aceleration;

	if(inputManager.IsKeyDown(InputManager::S_KEY) && fabs(linearSpeed - aceleration) < maxSpeed)
		linearSpeed -= aceleration;

	if(inputManager.IsKeyDown(InputManager::A_KEY))
		rotation -= angleSpeed;

	if(inputManager.IsKeyDown(InputManager::D_KEY))
		rotation += angleSpeed;

	if(inputManager.MousePress(InputManager::LEFT_MOUSE_BUTTON))
		Shoot();
	 
	speed->x = cos(rotation / 180 * PI) * linearSpeed;
	speed->y = sin(rotation / 180 * PI) * linearSpeed;

	box->x += speed->x;
	box->y += speed->y;
}

void Penguins::Render(){
	bodySp->Render(box->GetDrawX() + Camera::pos[0].x, box->GetDrawY() + Camera::pos[0].y, rotation);	
	cannonSp->Render(box->x - cannonSp->GetWidth() / 2 + Camera::pos[0].x, box->y - cannonSp->GetHeight() / 2 + Camera::pos[0].y, cannonAngle);	
}

bool Penguins::IsDead(){
	if(hp <= 0){
		Camera::Unfollow();
		return true;
	}
	
	return false;
}

void Penguins::Shoot(){
	const double PI = acos(-1);
	const double cannonAngleRad = cannonAngle / 180 * PI;

	double timeLimit = 1;

	if(timer.Get() > timeLimit){
		timer.Restart();

		Vec2 v;
		v.transform(cannonSp->GetWidth() / 2.0, cannonAngleRad);

		Bullet *bullet = new Bullet(box->GetDrawX() + v.x , box->GetDrawY() + v.y, cannonAngleRad, 100, 1000, "img/penguinbullet.png", 4, 6, false);

		Game::GetInstance()->GetState()->AddObject(bullet);
	}
}

void Penguins::NotifyCollision(GameObject &other){
	if(other.Is("bullet")){
		if(((Bullet &)other).targetsPlayer){
			hp -= 5;
			if(IsDead()){
				Animation *animation = new Animation(box->x, box->y, rotation, "img/penguindeath.png", 5, 1, 5, true);			
				Game::GetInstance()->GetState()->AddObject(animation);
			}
		}
	}
}

bool Penguins::Is(std::string type){
	return (type == "penguins");
}
