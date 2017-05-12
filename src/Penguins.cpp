#include "Penguins.h"

Penguins::Penguins(double x, double y){
	bodySp = Sprite("penguin.png");
	cannonSp = Sprite("cubngun.png");
	speed = new Vec2(0, 0);
	box = new Rect(x, y, bodySp.GetWidth(), bodySp.GetHeight());
	player = this;
}

Penguins::~Penguins(){
	player = nullptr;
}

Penguins::Update(double dt){
		
}
