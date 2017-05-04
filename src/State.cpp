#include "State.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Face.h"
#include "Alien.h"
#include "Vec2.h"
#include "Camera.h"

#include <cstdlib>
#include <cmath>

State::State(){
	quitRequested = false;

	bg = new Sprite();

	tileSet = new TileSet(64, 64, "img/tileset.png");
	tileMap = new TileMap("map/tileMap.txt", tileSet);

	Alien *alien = new Alien(512, 300, 5);
	objectArray.emplace_back(alien);
}

State::~State(){
	delete(bg);
	objectArray.clear();
}

void State::LoadAssets(){
	bg->Open("img/ocean.jpg");
}

void State::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();
	Camera camera;

	inputManager.Update();

	camera.Update(dt);
	
	if(inputManager.KeyPress(SDLK_ESCAPE) || inputManager.QuitRequested()){
		quitRequested = true;
	}

	if(inputManager.KeyPress(SDLK_SPACE)){
		//AddObject((double)inputManager.GetMouseX(), (double)inputManager.GetMouseY());
	}

	for(auto it = objectArray.begin(); it < objectArray.end(); it++){
		(*it)->Update(dt);

		if((*it)->IsDead())
			objectArray.erase(it);
	}
}

void State::Render(){
	bg->Render(0, 0);

	tileMap->RenderLayer(0, Camera::pos);

	for(auto &it : objectArray)
		it->Render();

	tileMap->RenderLayer(1, Camera::pos);
}

/*
void State::AddObject(double mouseX, double mouseY){
	double angle = ((rand() % 360) * acos(-1))/180.0;
	
	Vec2 *vec = new Vec2(mouseX, mouseY);

	vec = vec->translate(200, 0);
	vec = vec->rotate(angle, mouseX, mouseY);

	Face *face = new Face(vec->x, vec->y);

	delete(vec);

	objectArray.emplace_back(face);
}*/

bool State::QuitRequested(){
	return quitRequested;
}
