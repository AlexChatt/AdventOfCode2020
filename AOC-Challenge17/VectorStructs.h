#pragma once


struct Vector3
{
	int X;
	int Y;
	int Z;

	Vector3(int x, int y, int z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};

struct Vector4
{
	int X;
	int Y;
	int Z;
	int W;

	Vector4(int x, int y, int z, int w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
};