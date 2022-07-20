#include "Renderer.h"

//uint32_t* colorBuffer = new uint32_t[480000];

Renderer::~Renderer()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}


void Renderer::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	/*if(fullscreenMode)
	{
		SDL_GetCurrentDisplayMode(0, m_displayMode);
	}*/

	m_window = SDL_CreateWindow("3DRenderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
	assert(m_window != NULL);

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	assert(m_renderer != NULL);

	m_colorbufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
	assert(m_colorbufferTexture != NULL);

	if (fullscreenMode) { SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN); }

	

	// Cube Face Vertex Draw Call Test

	/*for (const auto& faceIndex : testCube.cubeFaces)
	{
		Vec3 faceVerts;
		faceVerts.x = faceIndex.x - 1;
		faceVerts.y = faceIndex.y - 1;
		faceVerts.z = faceIndex.z - 1;
		std::cout << faceVerts.x << " " << faceVerts.y << " " << faceVerts.z << std::endl;

	}*/



	// Point Draw Function

	/*for (float i = -1; i <= 1; i+=0.25)
	{
		for (float j = -1; j <= 1; j+=0.25)
		{
			for (float k = -1; k<=1; k+=0.25)
			{
				projectPoints.push_back(Vec3(i, j, k));
			}
		}
	}*/

	//std::cout << projectPoints.size() << std::endl;

	//int* colorBuffer = new int[480000];

	//std::vector<uint32_t>* colorBuffer = new std::vector<uint32_t>(480000);
	//colorBuffer.reserve(800 * 600);

	/*for (size_t j = 0; j < 600; j++)
	{
		for (size_t i = 0; i < 800; i++)
		{
			std::cout << colorBuffer[j * 800 + i] << std::endl;
		}*/

	//}
	m_triangleVertexPos.resize(12);
	initializeGraph();
	rendererActive = true;

	run();

}

void Renderer::run()
{
	while(rendererActive)
	{		
		// Process input
		processInput();


		// Update in-game elements
		update();		

		// Render to screen	
		render();
	
	}
}

void Renderer::processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			rendererActive = false;
		}
		if (event.key.keysym.sym == SDLK_1)
		{
			modifyStartNode = true;
			modifyEndNode = false;	
			std::cout << "Please Modify Start Node" << std::endl;
		}
		if (event.key.keysym.sym == SDLK_2)
		{
			modifyStartNode = false;
			modifyEndNode = true;
			std::cout << "Please Modify End Node" << std::endl;
		}

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			std::cout << "RMB Clicked" << std::endl;
			SDL_GetMouseState(&mouseCoordX, &mouseCoordY);
			isMousePressed = true;
		}
		break;
	case SDL_QUIT:
	{
		rendererActive = false;
		break;
	}
	}

}

void Renderer::render()
{
	debugGrid();
	

	//drawLine(100, 100, 200, 200);
	//drawLine(200, 200, 300, 100);
	//drawLine(300, 100, 100, 100);

	/*for (size_t i = 0; i < m_triangleVertexPos.size(); i++)
	{				
		TriangleVertexPos triangletoRender = m_triangleVertexPos[i];	

		drawRect(triangletoRender.vertexCoord[0].x + 400, triangletoRender.vertexCoord[0].y + 300, 4, 4, 0xFF0000FF);
		drawLine(triangletoRender.vertexCoord[0].x + 400, triangletoRender.vertexCoord[0].y + 300, triangletoRender.vertexCoord[1].x + 400, triangletoRender.vertexCoord[1].y + 300);
		drawRect(triangletoRender.vertexCoord[1].x + 400, triangletoRender.vertexCoord[1].y + 300, 4, 4, 0xFF0000FF);	
		drawLine(triangletoRender.vertexCoord[1].x + 400, triangletoRender.vertexCoord[1].y + 300, triangletoRender.vertexCoord[2].x + 400, triangletoRender.vertexCoord[2].y + 300);
		drawRect(triangletoRender.vertexCoord[2].x + 400, triangletoRender.vertexCoord[2].y + 300, 4, 4, 0xFF0000FF);			
		drawLine(triangletoRender.vertexCoord[2].x + 400, triangletoRender.vertexCoord[2].y + 300, triangletoRender.vertexCoord[0].x + 400, triangletoRender.vertexCoord[0].y + 300);

	}*/

	drawBuffer();
	//debugGrid(); 
	clearBuffer();
	//clearBuffer();


	SDL_RenderPresent(m_renderer); // presenting backbuffer
}

void Renderer::clearBuffer()
{
	for (size_t j = 0; j < 600; j++)
	{
		for (size_t i = 0; i < 800; i++)
		{
			//if ((j * 800 + i + 1) % 10 == 0) { colorBuffer[j * 800 + i] = 0x00000000; continue; }
			colorBuffer[j * 800 + i] = 0xFFFFFF00;
		}
	}
	//std::cout << colorBuffer[479999] << std::endl;

}

void Renderer::drawBuffer()
{
	//std::cout << " happening2 " << (int)sizeof(int) * 800 << std::endl;
	SDL_UpdateTexture(m_colorbufferTexture, NULL, colorBuffer, 800 * sizeof(uint32_t));
	SDL_RenderCopy(m_renderer, m_colorbufferTexture, NULL, NULL);
}	

void Renderer::debugGrid()
{


	for (size_t j = 0; j < 600; j++)
	{
		for (size_t i = 0; i < 800; i++)
		{
			if ((j * 800 + i + 1) % 10 == 0) { colorBuffer[j * 800 + i] = 0x00000000; }
		}
	}
	
	for (size_t i = 0; i < 600; i+=10)
	{
		for (size_t j = 0; j < 800; j++)
		{
			colorBuffer[i * 800 + j] = 0x00000000;
		}
	
	}

	for (const auto &tup: modifiedNodes)
	{
		int x = std::get<0>(tup);
		int y = std::get<1>(tup);
		uint32_t rectColor = std::get<2>(tup);
		drawRect(x, y, 10, 10, rectColor);
	}

}

void Renderer::drawRect(int x, int y, int width, int height, uint32_t rectColor)
{
	if (!(x < 800 && x > 0 && y < 600 && y > 0)) { std::cout << "Reposition rectangle coordinates, out of bounds" << std::endl; return; }
	//std::cout << "lol" << std::endl;
	//std::cout << x << " " << y << std::endl;
	for (size_t i = x; i < x + width; i++)
	{
		for (size_t j = y; j < y + height; j++)
		{
			//std::cout << i << " " << j << std::endl;
			colorBuffer[i + j * 800] = rectColor;			
		}
	}


}

void Renderer::update()
{
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), oldFrameTime + targetFPS)) { }
	int delayTime = targetFPS - (SDL_GetTicks() - oldFrameTime);
	//std::cout << delayTime << "\n";
	if (delayTime > 0) { SDL_Delay(delayTime); }
	oldFrameTime = SDL_GetTicks();
	updatedNodes();

	/*if (startNode != nullptr)
	{
		std::cout << startNode->x << " " << startNode->y << std::endl; 
		for (size_t i = 0; i < startNode->currentNeighbours.size(); i++)
		{
			std::cout << startNode->currentNeighbours[i]->x << " " << startNode->currentNeighbours[i]->y << std::endl;
		}
	}*/
	//if (endNode != nullptr) { std::cout << endNode->x << " " << endNode->y << std::endl; }
	//SDL_GetMouseState(&x, &y);
	//if (isMousePressed && modifyStartNode)
	//{
	//	//std::cout << "Mouse x coordinate " << mouseCoordX / 10 << " " << "Mouse y coordinate " << mouseCoordY / 10 << std::endl;
	//	int x = (mouseCoordX / 10) * 10, y = (mouseCoordY / 10) * 10;
	//	drawRect(x, y, 10, 10, 0x00FF00FF);
	//	isMousePressed = false;
	//}

	//if (isMousePressed && modifyEndNode)
	//{
	//	int x = (mouseCoordX / 10) * 10, y = (mouseCoordY / 10) * 10;
	//	drawRect(x, y, 10, 10, 0x00008000);
	//	isMousePressed = false;
	//}




	// 3D Graphics Related Stuff
	// cubeRot += 0.01f;
	//for (size_t i = 0; i < testCube.cubeFaces.size(); i++)
	//{
	//	std::vector<Vec3> faceVerts; // Replace this later with a vector initialized at startup
	//	faceVerts.push_back(testCube.cubeVerts[testCube.cubeFaces[i].p1 - 1]);
	//	faceVerts.push_back(testCube.cubeVerts[testCube.cubeFaces[i].p2 - 1]);
	//	faceVerts.push_back(testCube.cubeVerts[testCube.cubeFaces[i].p3 - 1]);

	//	TriangleVertexPos triangleVerts;
	//	for (size_t j = 0; j < faceVerts.size(); j++)
	//	{
	//		Vec3 vertexPos = faceVerts[j];
	//		vertexPos = rotY(vertexPos, cubeRot);			
	//		float projectedpointX = (vertexPos.x * 128) / (vertexPos.z - 5.0f);
	//		float projectedpointY = (vertexPos.y * 128) / (vertexPos.z - 5.0f);
	//		triangleVerts.vertexCoord[j].x = projectedpointX;
	//		triangleVerts.vertexCoord[j].y = projectedpointY;
	//		triangleVerts.vertexCoord[j].z = vertexPos.z - 5.0f;

	//	}	
	//	m_triangleVertexPos[i] = triangleVerts;
	//}

	//for (const auto& faceIndex: testCube.cubeFaces)
	//{
	//	Vec3 faceVerts;
	//	faceVerts.x = faceIndex.p1 - 1;
	//	faceVerts.y = faceIndex.p2 - 1;
	//	faceVerts.z = faceIndex.p3 - 1;
	//	
	//	// Render vertex position		
	//	Vec3 vertexTransformRot = faceVerts;
	//	vertexTransformRot = rotY(vertexTransformRot, cubeRot);
	//	float projectedpointX = (vertexTransformRot.x * 640) / (vertexTransformRot.z - 5.0f);
	//	float projectedpointY = (vertexTransformRot.y * 640) / (vertexTransformRot.z - 5.0f);
	//	projectedVertexCoords-

	//	// Shove updated vertex positions into an array
	//}


}

void Renderer::drawLine(int x0, int y0, int x1, int y1)
{
	int deltaY = y1 - y0;
	int deltaX = x1 - x0;

	int incrementAxis = abs(deltaY) >= abs(deltaX) ? abs(deltaY) : abs(deltaX);

	float yVal = deltaY / (float)incrementAxis;
	float xVal = deltaX / (float)incrementAxis;

	float currentXVal = x0;
	float currentYVal = y0;

	for (int i = 0; i <= incrementAxis; i++)
	{
		drawRect(currentXVal, currentYVal, 5, 5, 0xFF2A0000);
		currentXVal += xVal;
		currentYVal += yVal;
	}

}

void Renderer::updatedNodes()
{

	if (isMousePressed && modifyStartNode && startNode == nullptr)
	{
		//std::cout << "Mouse x coordinate " << mouseCoordX / 10 << " " << "Mouse y coordinate " << mouseCoordY / 10 << std::endl;
		int x = (mouseCoordX / 10) * 10, y = (mouseCoordY / 10) * 10;
		std::cout << "Hit execution " <<  x << " " << y << " " << std::endl;
		//startNode = new MapNode;
		startNode = &mapGraph[(mouseCoordY/10) * 80 + (mouseCoordX/10)];
		//std::cout << &mapGraph[startNode->y * 80 + startNode->x] << std::endl;
		modifiedNodes.push_back(std::make_tuple(x, y, 0x00FF00FF));

		std::cout << startNode->x << " " << startNode->y << std::endl;
		for (size_t i = 0; i < startNode->currentNeighbours.size(); i++)
		{
			std::cout << startNode->currentNeighbours[i]->x << " " << startNode->currentNeighbours[i]->y << std::endl;
		}
				
		//drawRect(x, y, 10, 10, 0x00FF00FF);
		isMousePressed = false;
	}

	if (isMousePressed && modifyEndNode && endNode == nullptr)
	{
		int x = (mouseCoordX / 10) * 10, y = (mouseCoordY / 10) * 10;
		endNode = &mapGraph[(mouseCoordY / 10)* 80 + (mouseCoordX/10)];
		modifiedNodes.push_back(std::make_tuple(x, y, 0x00008000));
		//drawRect(x, y, 10, 10, 0x00008000);
		isMousePressed = false;
	}
	
	if (startNode != nullptr && endNode != nullptr && !checkAStar)
	{
		aStarAlgorithm();
		//std::cout << "Done" << std::endl;
	}


	/*if (endNode != nullptr)
	{
		std::cout << "kik" << std::endl;
		MapNode* temp = endNode;
		while (temp->parentNode != nullptr)
		{
			modifiedNodes.push_back(std::make_tuple(temp->x * 10, temp->y * 10, 0x00FF000000));
			temp = temp->parentNode;
		}
	}*/
}

void Renderer::initializeGraph()
{
	
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			mapGraph[j * 80 + i].x = i;
			mapGraph[j * 80 + i].y = j;
			mapGraph[j * 80 + i].hasVisited = false;
			mapGraph[j * 80 + i].pathfromStart = std::numeric_limits<float>::max();
			mapGraph[j * 80 + i].pathtoEnd = std::numeric_limits<float>::max();
			mapGraph[j * 80 + i].parentNode = nullptr;
		
		}
	}

	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (i > 0)
			{
				mapGraph[j * 80 + i].currentNeighbours.push_back(&mapGraph[j * 80 + (i - 1)]);
			}
			if (j > 0)
			{
				mapGraph[j * 80 + i].currentNeighbours.push_back(&mapGraph[(j - 1) * 80 + i]);
			}
			if (i < 79)
			{
				mapGraph[j * 80 + i].currentNeighbours.push_back(&mapGraph[j * 80 + (i + 1)]);
			}
			if (j < 59)
			{
				mapGraph[j * 80 + i].currentNeighbours.push_back(&mapGraph[(j + 1) * 80 + i]);
			}
		}
	}

}

void Renderer::aStarAlgorithm()
{
	MapNode* currNode = startNode;
	startNode->pathfromStart = 0;
	startNode->pathtoEnd = distToPath(startNode, endNode);
	
	std::vector<MapNode*> checkedNodes;
	checkedNodes.push_back(startNode);

	while(checkedNodes.size() && currNode != endNode)
	{
		std::sort(checkedNodes.begin(), checkedNodes.end(), [](const MapNode* lhs, const MapNode* rhs)
			{
				return lhs->pathtoEnd < rhs->pathtoEnd;
			});
	
		while(checkedNodes.size() && checkedNodes.front()->hasVisited)
		{
			checkedNodes.erase(checkedNodes.begin());
		}

		if (!checkedNodes.size())
		{
			break;
		}

		currNode = checkedNodes.front();
		currNode->hasVisited = true;

		for (auto& neighbouringNode: currNode->currentNeighbours)
		{
			if (!neighbouringNode->hasVisited)
			{
				checkedNodes.push_back(neighbouringNode);
			}

			float distCheck = currNode->pathfromStart + distToPath(currNode, neighbouringNode);
			if (distCheck < neighbouringNode->pathfromStart)
			{
				modifiedNodes.push_back(std::make_tuple(neighbouringNode->x * 10, neighbouringNode->y * 10, 0x00FF0000));
				neighbouringNode->parentNode = currNode;
				neighbouringNode->pathfromStart = distCheck;
				neighbouringNode->pathtoEnd = neighbouringNode->pathfromStart + distToPath(neighbouringNode, endNode);
			}		
		}
	}
	if (endNode != nullptr)
	{
		//std::cout << "kik" << std::endl;
		MapNode* temp = endNode;
		while (temp ->parentNode != nullptr)
		{
			//std::cout << temp->x << " " << temp->y << std::endl;
			modifiedNodes.push_back(std::make_tuple(temp->x * 10, temp->y * 10, 0x00FF000000));
			temp = temp->parentNode;
		}
	}
	checkAStar = false;
}