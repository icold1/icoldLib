#include "mylib.hpp"

using namespace myLib;

int main()
{
	Point a(1, 2), b (3, 4);
	Point c(1, 2.);
	printc("test", 1, 2., Line(a,b)==Line(c,b));
}