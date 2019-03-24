#pragma once
class TspBB
{
	int cities;
	int lowerBound;
	int upperBound;
	int minTourCost;
	int **edge;
	int path[40];

public:
	TspBB(int **edge, int cities);

	void tspR(int **edge, int currCost, int currVertex, int lvl);
	void branchNbound();
	int reduceMatrix(int **redEdge);
	~TspBB();
};

