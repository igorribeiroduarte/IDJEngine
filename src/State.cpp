#include "State.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Face.h"
#include "Alien.h"
#include "Vec2.h"
#include "Camera.h"
#include "Penguins.h"
#include "Collision.h"

#include <cstdlib>
#include <cmath>

State* State::instance = nullptr;

State::State(){
	quitRequested = false;

	bg = new Sprite();

	tileSet = new TileSet(64, 64, "img/tileset.png");
	tileMap = new TileMap("map/tileMap.txt", tileSet);

	Alien *alien = new Alien(512, 300, 5);
	objectArray.emplace_back(alien);

	Penguins *penguins = new Penguins(704, 640);
	Camera::Follow(penguins);
	objectArray.emplace_back(penguins);
}

State::~State(){
	delete(bg);
	objectArray.clear();
}

void State::LoadAssets(){
	bg->Open("img/ocean.jpg");
}

int aux = 0;

void State::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();
	Camera camera;

	inputManager.Update();

	camera.Update(dt);
	
	if(inputManager.KeyPress(SDLK_ESCAPE) || inputManager.QuitRequested()){
		quitRequested = true;
	}

	for(int it = 0; it < (int)objectArray.size(); it++){
		objectArray[it]->Update(dt);

		if(objectArray[it]->IsDead()){
			objectArray.erase(objectArray.begin() + it);
			break;
		}
	}

	
	for(int it = 0; it < (int)objectArray.size(); it++){
		for(int it2 = it + 1; it2 < (int)objectArray.size(); it2++){
			Rect itBox = *objectArray[it]->box;
			Rect it2Box = *objectArray[it2]->box;

			itBox.x = itBox.GetDrawX() + Camera::pos[0].x;
			itBox.y = itBox.GetDrawY() + Camera::pos[0].y ;

			it2Box.x = it2Box.GetDrawX() + Camera::pos[0].x;
			it2Box.y = it2Box.GetDrawY() + Camera::pos[0].y; 

			double itAngle = objectArray[it]->rotation;
			double it2Angle = objectArray[it2]->rotation;

			if(Collision::IsColliding(itBox, it2Box, itAngle, it2Angle)){
				objectArray[it]->NotifyCollision(*objectArray[it2]);
				objectArray[it2]->NotifyCollision(*objectArray[it]);
			}
		}
	}
	
}

void State::Render(){
	bg->Render(0, 0);

	tileMap->RenderLayer(0, Camera::pos);

	for(auto &it : objectArray)
		it->Render();

	tileMap->RenderLayer(1, Camera::pos);
}

void State::AddObject(GameObject *ptr){
	objectArray.emplace_back(ptr);
}

bool State::QuitRequested(){
	return quitRequested;
}
