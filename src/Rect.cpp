#include "Rect.h"

Rect::Rect(double px, double py, double w, double h){
	x = px;
	y = py;
	width = w;
	height = h;
}

double Rect::GetDrawX(){
	return x - width / 2;
}

double Rect::GetDrawY(){
	return y - height / 2;
}

bool Rect::IsInside(double px, double py){
	bool inside;

	if(px>=x && px<=x+width && py>=y && py<=y+height)
		inside = true;
	else
		inside = false;

	return inside;
}

Rect Rect::GetCenter(){
	return Rect(x + width / 2, y + height / 2);
}
