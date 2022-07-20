#pragma once
#include <math.h>
#include <vector>

struct Vec3
{
	Vec3(float v1 = 0.0f, float v2 = 0.0f, float v3 = 0.0f) : x(v1), y(v2), z(v3) {}
	float x;
	float y;
	float z;
};

struct Vec3i
{
	Vec3i(int v1 = 0, int v2 = 0, int v3 = 0) : p1(v1), p2(v2), p3(v3) {}
	int p1;
	int p2;
	int p3;
};

struct TriangleVertexPos
{
	TriangleVertexPos() = default;
	~TriangleVertexPos() = default;
	Vec3 vertexCoord[3];

};

struct Triangle
{
	Triangle() = default;
	~Triangle() = default;
	Vec3 triangleVerts[3];

};

Vec3 rotZ(const Vec3& rotateVec, float angle);
Vec3 rotY(const Vec3& rotateVec, float angle);
Vec3 rotX(const Vec3& rotateVec, float angle);


struct MapNode
{
	int x, y;
	bool hasVisited = false;
	float pathfromStart;
	float pathtoEnd;
	std::vector<MapNode*> currentNeighbours;
	MapNode* parentNode = nullptr;

};

int distToPath(const MapNode* currentNode, const MapNode* goalNode);
	
