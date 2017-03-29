#include "Face.h"

Face::Face(double x, double y){
	sp = new Sprite("res/img/penguinface.png");
	box = new Rect(x, y, sp->GetWidth(), sp->GetHeight());
}

Face::~Face(){
	delete(sp);
	delete(box);
}

void Face::Damage(int damage){
	hitpoints -= damage;
}

void Face::Update(double){

}

void Face::Render(){
	sp->Render(box->x, box->y);
//	printf("%f %f\n", box->x, box->y);
}

bool Face::IsDead(){
	if(hitpoints <= 0)
		return true;
	else
		return false;
}
