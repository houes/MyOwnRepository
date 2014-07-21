#include "RMPL_MATH.h"
#include <vector>

class RotaryToZ
{
  MATH::Vector3 RotationAxis;
  float RotationDegree;
public:
	RotaryToZ();
	RotaryToZ(MATH::Vector3,float);
};


class Hole
{
	std::vector<MATH::Vector3> locations;
	float SampleInterval;
	std::vector<MATH::Vector3> CandidateAxes;

public:
	std::vector<MATH::Matrix44> trans_m;
	Hole();
	void AddHole(const MATH::Vector3 hole);
	void CalculateAxes();
	void CalculateTransition();

};