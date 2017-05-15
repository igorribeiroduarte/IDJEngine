#ifndef RECT_H
#define RECT_H

class Rect{
	public:
		//Left top point
		double x, y;
		double width, height;

		Rect(double px = 0, double py = 0, double w = 0, double h = 0);

		double GetDrawX();
		double GetDrawY();

		bool IsInside(double x, double y);

		Rect GetCenter();
};

#endif
