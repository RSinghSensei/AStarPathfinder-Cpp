#pragma once
#include <SDL.h>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include <assert.h>
#include <iostream>

#include "utils.h"
#include "meshGen.h"


class Renderer
{
public:
	Renderer() = default;
	~Renderer();

	void init();
	void processInput();
	void clearBuffer();
	void drawBuffer();
	void debugGrid();
	void update();
	void render();
	void run();


	void updatedNodes();
	void initializeGraph();

	void drawRect(int x, int y, int width, int height, uint32_t rectColor);
	void drawLine(int x0, int y0, int x1, int y1);
	void orthoProjection();

private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;
	SDL_Texture* m_colorbufferTexture = NULL;
	SDL_DisplayMode* m_displayMode = NULL;

	bool rendererActive = false;
	bool debugGridActive = true;
	bool fullscreenMode = false;
	uint32_t* colorBuffer = new uint32_t[480000];

	int FPS = 24;
	int targetFPS = 1000 / FPS;
	int oldFrameTime = 0;

	int mouseCoordX, mouseCoordY;
	bool isMousePressed = false;
	bool modifyStartNode = false;
	bool modifyEndNode = false;	
	std::vector<std::tuple<int, int, uint32_t>>modifiedNodes;
	MapNode* mapGraph = new MapNode[4800];
	MapNode* startNode = nullptr;
	MapNode* endNode = nullptr;
	void aStarAlgorithm();
	bool checkAStar = false;

	std::vector<Vec3>projectPoints;
	std::vector<Vec3>projectedVertexCoords;
	std::vector<TriangleVertexPos> m_triangleVertexPos;
	cubeMesh testCube;
	//std::vector<uint32_t>* colorBuffer;
	//uint32_t colorBuffer[];
	//int colorBuffer[];
	/*std::array <uint32_t, 480000> colorBuffer;*/

	float cubeRot = 0.0f;
};