#include "TitleState.h"

TitleState::TitleState(){
	bg = new Sprite("img/title.jpg");
}

TitleState::~TitleState(){
	delete(bg);
}

void TitleState::Update(double dt){
		
}

void TitleState::Render(){
	bg->Render(0, 0);
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
