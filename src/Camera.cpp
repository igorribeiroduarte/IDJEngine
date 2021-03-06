#include "Camera.h"

GameObject *Camera::focus;
Vec2 Camera::pos[6];
Vec2 Camera::speed[6];

void Camera::Follow(GameObject *newFocus){
	focus = newFocus;
}

void Camera::Unfollow(){
	focus = nullptr;
}

void Camera::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();

	speed[0].x = 0;
	speed[0].y = 0;

	speed[1].x = 0;
	speed[1].y = 0;

	if(focus){
		
	}else{
		if(inputManager.IsKeyDown(InputManager::RIGHT_ARROW_KEY)){
			speed[0].x = 1.0 / dt;
			speed[0].y = 0;

			speed[1].x = 0.5 / dt;
			speed[1].y = 0;
		}
		
		if(inputManager.IsKeyDown(InputManager::LEFT_ARROW_KEY)){
			speed[0].x = -1.0 / dt;
			speed[0].y = 0;

			speed[1].x = -0.5 / dt;
			speed[1].y = 0;
		}
		
		if(inputManager.IsKeyDown(InputManager::UP_ARROW_KEY)){
			speed[0].x = 0;
			speed[0].y = -1.0 / dt;

			speed[1].x = 0;
			speed[1].y = -0.5 / dt;
		}
		
		if(inputManager.IsKeyDown(InputManager::DOWN_ARROW_KEY)){
			speed[0].x = 0;
			speed[0].y = 1.0 / dt;

			speed[1].x = 0;
			speed[1].y = 0.5 / dt;
		}
	}

	pos[0].x += speed[0].x;
	pos[0].y += speed[0].y;

	pos[1].x += speed[1].x;
	pos[1].y += speed[1].y;
}
