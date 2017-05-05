#ifndef VEC2_H
#define VEC2_H

class Vec2{
	public:
		double x, y;
	
		Vec2();
		Vec2(double x, double y);

		double length();

		void normalize();

		Vec2 *translate(double dx, double dy);
		Vec2 *rotate(double pAngle);
		Vec2 *rotate(double pAngle, double px, double py);
		
		static double angle(double x, double y);

	private:
};

#endif
