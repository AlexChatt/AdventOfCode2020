// AOC-Challenge5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Plane.h"

int main()
{
	class Plane MyPlane;
	MyPlane.ReadInBordingLits("BordingList.txt");
	MyPlane.GetHightestSeatID();
	MyPlane.GetFreeSeat();
}
