#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "TSPdp.h"
#include <chrono>

using tp = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float,std::milli>;

TSPdp::TSPdp(int **edge, int cities)
{
	this->edge = edge;
	this->cities = cities;
	minTourCost = 0;
	endPosition = 0;
}

void TSPdp::tsp()
{
	endPosition = (1 << cities) - 1;

	rememberPath = new int*[cities];								
																	
	for (int i = 0; i < cities; i++) {								
		rememberPath[i] = new int[1 << cities];						
		for (int j = 0; j < 1 << cities; j++)						
			rememberPath[i][j] = -1;								
	}																
																	
	rememberDistance = new int*[cities];							
																	
	for (int i = 0; i < cities; i++) {								
		rememberDistance[i] = new int[1 << cities];					
		for (int j = 0; j < 1 << cities; j++)						
			rememberDistance[i][j] = -1;							
	}																

	tp start = std::chrono::system_clock::now();				

	minTourCost = findMinTourCost(0, 1);							

	duration d = std::chrono::system_clock::now() - start;			

	std::cout <<"Time: " << d.count() << "\n";									

	std::cout << "Min distance: " << minTourCost;										

	getPath();														
}


int TSPdp::findMinTourCost(int currentVertex, int position)
{
	int vertex;

	if (position == endPosition)									
	{																
		return edge[currentVertex][0];								
	}

	if (rememberDistance[currentVertex][position] != -1)
	{															
		return rememberDistance[currentVertex][position];			
	}

	int distance = INT32_MAX;

	for (int nextVertex = 0; nextVertex < cities; nextVertex++)		
	{
		if ((position&(1 << nextVertex)) != 0)						
		{
			continue;
		}

		int nextPosition = position | (1 << nextVertex);

		int newDistance = edge[currentVertex][nextVertex] + findMinTourCost(nextVertex, nextPosition);

		if (newDistance < distance)
		{
			distance = newDistance;
			vertex = nextVertex;
		}
	}
	rememberPath[currentVertex][position] = vertex;
	return rememberDistance[currentVertex][position] = distance;
}

void TSPdp::getPath()												
{

	int j = 0;
	int position = 1;
	int currentVertex = 0;
	while (true) {
		path[j] = currentVertex;
		j++;
		int i = rememberPath[currentVertex][position];
		if (i == -1) break;
		int nextPosition = position | (1 << i);
		position = nextPosition;
		currentVertex = i;
	}
	path[j] = 0;

	std::cout << "\nPath: ";
	for (int i = 0; i < j; i++)
	{
		std::cout << path[i] << " -> ";
	}
	std::cout << path[j];
}

TSPdp::~TSPdp()
{
	for (int i = 0; i < cities; i++) {
		delete[] rememberPath[i];
	}
	delete[] rememberPath;


	for (int i = 0; i < cities; i++) {
		delete[] rememberDistance[i];
	}
	delete[] rememberDistance;

	for (int i = 0; i < cities; i++) {
		delete[] edge[i];
	}
	delete[] edge;

}
