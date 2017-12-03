#include "vector_math.h"
#include <math.h>



Vector2d intersect_lines(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	//Ax + By = C
	int A1 = y2 - y1;
	int B1 = x1 - x2;
	int C1 = (A1 * x1) + (B1 * y1);

	int A2 = y4 - y3;
	int B2 = x3 - x4;
	int C2 = (A2 * x3) + (B2 * y3);

	Vector2d vect = { 0, 0 };
	//

	double det = A1*B2 - A2*B1;

	if (det == 0) {
		//Lines are parallel
		return vect;
	}
	else {
		//double x = (B2*C1 - B1*C2) / det
		//	double y = (A1*C2 - A2*C1) / det

		vect.x = (double)(B2 * C1 - B1 * C2) / det;
		vect.y = (double)(A1 * C2 - A2 * C1) / det;
	}
	return vect;
}