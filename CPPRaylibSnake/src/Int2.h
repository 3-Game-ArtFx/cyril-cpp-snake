#pragma once

struct Int2
{
	int x;
	int y;

	Int2(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}

	Int2 operator = (Int2 other)
	{
		x = other.x;
		y = other.y;
		return other;
	}

	Int2 operator + (Int2 other)
	{
		Int2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Int2 operator * (int other)
	{
		Int2 result;
		result.x = x * other;
		result.y = y * other;
		return result;
	}

	bool operator == (Int2 other)
	{
		return x == other.x && y == other.y;
	}
};
