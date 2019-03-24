#include "stdafx.h"
#include "ReadFile.h"
#include <iostream>
#include <fstream>


ReadFile::ReadFile()
{
}

int **ReadFile::openFile(int &cities)
{
	int **edge;
	std::ifstream in("miasta.txt");

	if (!in) {
		std::cout << "Nie mozna otworzyc pliku.\n";
		return 0;
	}
	in >> cities;

	edge = new int*[cities];

	for (int i = 0; i < cities; i++) {

		edge[i] = new int[cities];

		for (int j = 0; j < cities; j++) {
			
			in >> edge[i][j];
			
			if(j == i)
				edge[i][j] = -1;
		}
	}

	in.close();
	return edge;
}


ReadFile::~ReadFile()
{
}
