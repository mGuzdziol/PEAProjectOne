#pragma once
class TSPbruteForce
{
	int **edge;
	int cities;
	int newDistance;
	int **num;
	int *vertex;
	int path[20];

public:
	TSPbruteForce(int **edge, int cities);
	void tsp();
	void swap(int *x, int *y);
	void permute(int l, int r);
	void findMinTourCost(int perm[]);
	~TSPbruteForce();
};

