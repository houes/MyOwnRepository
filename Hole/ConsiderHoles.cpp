#include "ConsiderHoles.h"


MATH::Segment3 FromVectorToSegment(MATH::Vector3 v)
{
	MATH::Segment3 s(MATH::Point3(0,0,0),MATH::Point3(0,0,0));
	s.point[1].x=v.x;
	s.point[1].y=v.y;
	s.point[1].z=v.z;
	return s;
}

MATH::Vector3 FromSegmentToVector(MATH::Segment3 s)
{
	MATH::Vector3 v(0,0,0);
	v.x=s.point[1].x;
	v.y=s.point[1].y;
	v.z=s.point[1].z;
	return v;
}

RotaryToZ::RotaryToZ()
{
       RotationDegree=0;
}

RotaryToZ::RotaryToZ(MATH::Vector3 v,float a)
{
	RotationAxis=v;
	RotationDegree=a;
}

Hole::Hole()
{
	SampleInterval=60.0;
}

void Hole::AddHole(const MATH::Vector3 hole)
{
	locations.push_back(hole);
}


void Hole::CalculateAxes()
{
	MATH::Vector3 a1;
	MATH::Segment3 a1s;

	if(locations.size()==1)
	{
		a1.x=locations[0].y;
		a1.y=-locations[0].x;
		a1.z=0;
		a1.normalize();
		if(a1.length()==0) {a1.x=1;a1.y=0;a1.z=0;}
		CandidateAxes.push_back(a1);

		for(int i=1;i<180.0/SampleInterval;i++)
		{
		a1s=FromVectorToSegment(a1);
		MATH::Matrix44 m(SampleInterval,locations[0]);
		a1s.transform(m);
		a1=FromSegmentToVector(a1s);
		CandidateAxes.push_back(a1);
		}


	}


}

void Hole::CalculateTransition()
{
	MATH::Vector3 k;
	float angle;
	//std::vector<RotaryToZ> transition;
	typedef std::vector<MATH::Vector3>::iterator VecPtr;

	for(VecPtr i=CandidateAxes.begin();i<CandidateAxes.end();i++)
	{
		k.x=i->y;
		k.y=-i->x;
		k.z=0;
		k.normalize();
		angle=i->angle_to(MATH::Vector3(0,0,1));
		//RotaryToZ t(k,angle);
		//transition.push_back(t);
		MATH::Matrix44 m(-angle,k);
		trans_m.push_back(m);
	}


}