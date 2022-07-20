#pragma once
#include "utils.h"
#include <vector>

struct cubeMesh
{
	cubeMesh() = default;
	~cubeMesh() = default;
	const std::vector<Vec3>cubeVerts
	{
		{-1, -1,  -1},
		{-1,  1,  -1},
		{1,   1,  -1},
		{1,  -1,  -1},
		{1,   1,   1},
		{1,  -1,   1},
		{-1,  1,   1},
		{-1, -1,   1}
	};
	const std::vector<Vec3i>cubeFaces
	{
		{1, 2, 3},
		{1, 3, 4},
		{4, 3, 5},
		{4, 5, 6},
		{6, 5, 7},
		{6, 7, 8},
		{8, 7, 2},
		{8, 2, 1},
		{2, 7, 5},
		{2, 5, 3},
		{6, 8, 1},
		{6, 1, 4}
	};
};
