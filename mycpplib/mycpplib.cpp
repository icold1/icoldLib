#include "mylib.hpp"

using namespace myLib;

int main()
{
	Point a(0, 0), b(5, 0), c(12,0);
	Triangle tri1{ a,b,c };
	printc(tri1.getCircumcircle(), "area:",tri1.getArea());
}
