#pragma once

#include <iostream>

struct WayPoint
{
public:
	int NorthSouthUnits;
	int EastWestUnits;

	void SetWayPoint(int16_t NSVal, int16_t EWVal);

	void MoveWayPointNorthWest(int16_t Value);
	void MoveWayPointEastWest(int16_t Value);

	void RotateWayPoint(int16_t RotationValue);

};
