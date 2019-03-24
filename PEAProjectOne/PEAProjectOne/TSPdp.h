#pragma once
class TSPdp
{
	int cities;
	int minTourCost;
	int **edge;
	int path[40];
	int **rememberPath;
	int endPosition;
	int **rememberDistance;

public:
	TSPdp(int **edge, int cities);
	void tsp();
	int findMinTourCost(int currentVertex, int position);
	void getPath();
	~TSPdp();
};

