#include "TitleState.h"
#include "Timer.h"
#include "InputManager.h"
#include "StageState.h"
#include "Game.h"

TitleState::TitleState(){
	bg = new Sprite("img/title.jpg");
	text = new Text("font/Call me maybe.ttf", 45, Text::TextStyle::SOLID, "Press space to start the game", {0, 0, 0, 255}, 500, 530);
}

TitleState::~TitleState(){
	delete(bg);
}

void TitleState::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();

	inputManager.Update();

	if(inputManager.KeyPress(InputManager::ESCAPE_KEY) || inputManager.QuitRequested())
		quitRequested = true;

	if(inputManager.KeyPress(InputManager::SPACE_KEY)){
		Game::GetInstance()->Push(new StageState());
		popRequested = true;
	}

	text->SetVisibility(true);

	timer.Update(dt);

	if(timer.Get() <= 0.3)
		text->SetVisibility(true);
	else if(timer.Get() <= 0.6)
		text->SetVisibility(false);
	else
		timer.Restart();
}

void TitleState::Render(){
	bg->Render(0, 0);
	text->Render();
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}

void TitleState::LoadAssets(){
}
