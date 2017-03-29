#include "Rect.h"

Rect::Rect(double px, double py, double w, double h){
	x = px - w/2;
	y = py - h/2;
	width = w;
	height = h;
}

bool Rect::IsInside(double px, double py){
	bool inside;

	if(px>=x && px<=x+width && py>=y && py<=y+height)
		inside = true;
	else
		inside = false;

	return inside;
}
