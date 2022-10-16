#pragma once
#include <vector>
#include "Int2.h"

template <typename T>
class Array2D
{
private:
	std::vector<std::vector<T>> array;

public:
	Array2D(T defaultValue, Int2 size = Int2())
	{
		array.resize(size.x);
		for (int i = 0; i < array.size(); i++)
		{
			array[i].resize(size.y);
			for (int j = 0; j < array[i].size(); j++)
			{
				array[i][j] = defaultValue;
			}
		}
	}
	~Array2D(){}

	void Resize(T defaultValue, Int2 newSize)
	{
		std::vector<std::vector<T>> oldArray;

		array.resize(newSize.x);
		for (int i = 0; i < array.size(); i++)
		{
			array[i].resize(newSize.y);
			for (int j = 0; j < array[i].size(); j++)
			{
				if (i < oldArray.size())
				{
					if (j < oldArray[i].size())
					{
						array[i][j] = oldArray[i][j];
						continue;
					}
				}
				array[i][j] = defaultValue;
			}
		}
	}


	void SetValue(Int2 index, T newValue)
	{
		if (array.size() > index.x)
		{
			if (array[index.x].size() > index.y)
			{
				array[index.x][index.y] = newValue;
			}
		}
	}

	T GetValue(Int2 index)
	{
		if (array.size() > index.x)
		{
			if (array[index.x].size() > index.y)
			{
				return array[index.x][index.y];
			}
		}
	}

	int GetSizeX()
	{
		return array.size();
	}

	int GetSizeY(int xIndex)
	{
		if (array.size() > xIndex)
		{
			return array[xIndex].size();
		}
		return 0;
	}
};

