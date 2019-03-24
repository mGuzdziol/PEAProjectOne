#include "stdafx.h"
#include "TSPbruteForce.h"
#include <iostream>
#include <fstream>
#include <chrono>

using tp = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float, std::milli>;

TSPbruteForce::TSPbruteForce(int **edge, int cities)
{
	this->edge = edge;
	this->cities = cities;
	newDistance = INT32_MAX;
}

void TSPbruteForce::tsp()
{
	vertex = new int[cities - 1];

	for (int i = 0; i < cities - 1; i++) {									
		vertex[i] = i + 1;													
	}

	std::cout << "\n";

	tp start = std::chrono::system_clock::now();							
	permute(0, cities - 1);
	duration d = std::chrono::system_clock::now() - start;					

	std::cout << "Time: " << d.count() << "\n";											

	std::cout << "Min distance: " << newDistance;												

	std::cout << "\nPath: ";

	for (int i = 0; i < cities + 1; i++)									
	{
		std::cout << path[i];
		if (i != cities)
			std::cout << " -> ";
	}
}

void TSPbruteForce::swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void TSPbruteForce::permute(int l, int r)
{
	if (l == r) {
		findMinTourCost(vertex);
		//for(int i=0; i<cities-1; i++)
			//std::cout << vertex[i];
		//std::cout << "\n";
	}
	else
	{
		for (int i = l; i < r; i++)
		{
			swap((vertex + l), (vertex + i));
			permute(l + 1, r);
			swap((vertex + l), (vertex + i));
		}
	}
}

void TSPbruteForce::findMinTourCost(int num[])
{
	int distance = 0;
	int tmp = 0;

	path[0] = 0;
	path[cities] = 0;

	for (int i = 0; i < cities; i++)
	{

		if (i == 0) {
			distance = distance + edge[0][num[i]];
			tmp = num[i];
		}

		if (i != 0 && i != cities - 1) {

			distance = distance + edge[tmp][num[i]];
			tmp = num[i];
		}

		if (i == cities - 1)
		{
			distance = distance + edge[tmp][0];
		}
	}

	if (distance < newDistance)
	{
		newDistance = distance;

		for (int i = 1; i < cities; i++)
			path[i] = num[i%cities - 1];
	}
	distance = 0;
}

TSPbruteForce::~TSPbruteForce()
{
	for (int i = 0; i < cities; ++i) {
		delete[] edge[i];
	}
	delete[] edge;

	delete[] vertex;
}
