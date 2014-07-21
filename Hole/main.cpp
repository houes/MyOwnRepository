#include "ConsiderHoles.h"

int main()
{
	//branch 1
	Hole a;
	a.AddHole(MATH::Vector3(1,0,0));
	a.CalculateAxes();
	a.CalculateTransition();

return 0;
}