#include "../../include/engine/frustumplane.h"


FrustumPlane::FrustumPlane(){}


FrustumPlane::FrustumPlane(float newA, float newB, float newC, float newD) {
	A = newA;
	B = newB;
	C = newC;
	D = newD;
}


float FrustumPlane::distance(Point p) {
	return A * p.x + B * p.y + C * p.z + D;
}


int FrustumPlane::boxInNormalSide(vector<Point> box) {
	for (int i = 0; i < box.size(); i++) {
		printf("%f\n", distance(box[i]));
		if (distance(box[i]) < 0) return 0;
	}

	return 1;
}