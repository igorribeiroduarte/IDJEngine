#include "State.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Face.h"
#include "Alien.h"
#include "Vec2.h"
#include "Camera.h"
#include "Penguins.h"

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
