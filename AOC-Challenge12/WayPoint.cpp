#include "WayPoint.h"

void WayPoint::SetWayPoint(int16_t NSVal, int16_t EWVal)
{
	NorthSouthUnits = NSVal;
	EastWestUnits = EWVal;
}

void WayPoint::MoveWayPointNorthWest(int16_t Value)
{
	NorthSouthUnits += Value;
}

void WayPoint::MoveWayPointEastWest(int16_t Value)
{
	EastWestUnits += Value;
}

void WayPoint::RotateWayPoint(int16_t RotationValue)
{
	int16_t TmpHolder;

	if (RotationValue > 0)
	{
		for (int i = 0; i < RotationValue; i += 90)
		{
			TmpHolder = NorthSouthUnits;
			NorthSouthUnits = -EastWestUnits;
			EastWestUnits = TmpHolder;
		}
	}
	else
	{
		for (int i = 0; i > RotationValue; i -= 90)
		{
			TmpHolder = EastWestUnits;
			EastWestUnits = -NorthSouthUnits;
			NorthSouthUnits = TmpHolder;
		}
	}
}