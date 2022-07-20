#include "utils.h"

Vec3 rotZ(const Vec3& rotateVector, float angle)
{
	float rotatedX = rotateVector.x * cosf(angle) - rotateVector.y * sinf(angle);
	float rotatedY = rotateVector.x * sinf(angle) + rotateVector.y * cosf(angle);
	Vec3 rotatedVectorP{ rotatedX, rotatedY, rotateVector.z };
	return rotatedVectorP;
}

Vec3 rotY(const Vec3& rotateVector, float angle)
{
	float rotatedX = rotateVector.x * cosf(angle) - rotateVector.z * sinf(angle);
	float rotatedZ = rotateVector.x * sinf(angle) + rotateVector.z * cosf(angle);
	Vec3 rotatedVectorP{ rotatedX, rotateVector.y, rotatedZ};
	return rotatedVectorP;

}

Vec3 rotX(const Vec3& rotateVector, float angle)
{
	float rotatedY = rotateVector.y * cosf(angle) - rotateVector.z * sinf(angle);
	float rotatedZ = rotateVector.y * sinf(angle) + rotateVector.z * cosf(angle);
	Vec3 rotatedVectorP{ rotateVector.x, rotatedY, rotatedZ};
	return rotatedVectorP;

}

void drawLine(int x0, int x1, int y0, int y1)
{
	int deltaY = y1 - y0;
	int deltaX = x1 - x0;

	int incrementAxis = abs(deltaY) >= abs(deltaX) ? abs(deltaY) : abs(deltaX);

	int yVal = deltaY / incrementAxis;
	int xVal = deltaX / incrementAxis;

	for (int i = 0; i < incrementAxis; i++)
	{
		
	}

}

int distToPath(const MapNode* currentNode, const MapNode* goalNode)
{
	int a = currentNode->x - goalNode->x;
	int b = currentNode->y - goalNode->y;
	int res = sqrtf((a * a) + (b * b));
	return res;
}
