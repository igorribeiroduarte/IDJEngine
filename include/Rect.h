#ifndef RECT_H
#define RECT_H

class Rect{
	public:
		//Left top point
		double x, y;

		double width, height;

		Rect(double px, double py, double w, double h);

		bool IsInside(double x, double y);
};

#endif
