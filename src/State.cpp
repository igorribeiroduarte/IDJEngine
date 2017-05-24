#include "State.h"

State::State(){
	popRequested = quitRequested = false;
}

State::~State(){
	objectArray.clear();
}

void State::AddObject(GameObject *object){
	objectArray.emplace_back(object);
}

bool State::PopRequested(){
	return popRequested;
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::UpdateArray(double dt){
	for(int i = 0; i < (int)objectArray.size(); i++)
		objectArray[i]->Update(dt);
}

void State::RenderArray(){
	for(int i = 0; i < (int)objectArray.size(); i++)
		objectArray[i]->Render();
}
