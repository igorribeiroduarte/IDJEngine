#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "TitleState.h"

EndState::EndState(StateData stateData){
	if(stateData.playerVictory){
		bg = new Sprite("img/win.jpg");
		music = Music("audio/endStateWin.ogg");
	}else{
		bg = new Sprite("img/lose.jpg");
		music = Music("audio/endStateLose.ogg");
	}

	instruction = new Text("font/Call me maybe.ttf", 30, Text::TextStyle::SOLID, "Pressione ESC para ir ao menu, ou espaco para tentar de novo.", {0, 0, 0, 255}, 500, 560);
}

void EndState::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();

	inputManager.Update();

	quitRequested = inputManager.QuitRequested();

	if(inputManager.KeyPress(InputManager::ESCAPE_KEY)){
		Game::GetInstance()->Push(new TitleState());
		popRequested = true;
		return;
	}

	if(inputManager.KeyPress(InputManager::SPACE_KEY)){
		Game::GetInstance()->Push(new StageState());
		popRequested = true;
		return;
	}
}

void EndState::Render(){
	bg->Render(0, 0);
	instruction->Render();
}

void EndState::Pause(){

}

void EndState::Resume(){

}

void EndState::LoadAssets(){

}
