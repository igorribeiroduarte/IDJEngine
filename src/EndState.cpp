#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"

EndState::EndState(StateData stateData){
	if(stateData.playerVictory){
		bg = new Sprite("img/win.jpg");
		music = Music("audio/endStateWin.ogg");
	}else{
		bg = new Sprite("img/lose.jpg");
		music = Music("audio/endStateLose.ogg");
	}

	instruction = Text("font/Call me maybe.ttf", 45, Text::TextStyle::SOLID, "Pressione ESC para ir ao menu, ou espaço para tentar de novo.", {0, 0, 0, 255}, 500, 530);
}

void EndState::Update(double dt){
	InputManager &inputManager = InputManager::GetInstance();

	inputManager.Update();

	quitRequested = inputManager.QuitRequested();

	if(inputManager.KeyPress(InputManager::ESCAPE_KEY))
		popRequested = true;

	if(inputManager.KeyPress(InputManager::SPACE_KEY)){
		Game::GetInstance()->Push(new StageState());
		popRequested = true;
	}
}

void EndState::Render(){
	bg->Render(0, 0);
	instruction.Render();
}

void EndState::Pause(){

}

void EndState::Resume(){

}

void EndState::LoadAssets(){

}
