#include "stdafx.h"
#include <iostream>
#include "TSPbruteForce.h"
#include "TSPdp.h"
#include "TspBB.h"
#include "ReadFile.h"
#include <ctime>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int **randomGraph( int cities)
{
	int **edge;

	srand(time(NULL));

	edge = new int*[cities];

	for (int i = 0; i < cities; i++) {

		edge[i] = new int[cities];

		for (int j = 0; j < cities; j++) {

			edge[i][j]= (std::rand() % 1000 ) + 1;

			if (j == i)
				edge[i][j] = -1;
		}
	}

	return edge;
}


int main()
{
	int cities;
	int choice=-1;
	int choice2 = -1;

	ReadFile readFile;

	int **edge; 
	int **edge2;

	std::cout << "Maksymilian Guzdziol, 233534. PEA-etap1\n\n";

	std::cout << "Podaj sposob uzyskania macierzy wag:\n";
	std::cout << "1. Wczytywanie macierzy wag z pliku\n";
	std::cout << "2. Losowanie macierzy wag\n";
	std::cin >> choice2;

	if (choice2 == 1)
	{
		edge = readFile.openFile(cities);

		edge2 = new int*[cities];
		for (int i = 0; i < cities; i++) {
			edge2[i] = new int[cities];
		}
	}
	else
	{
		std::cout << "Podaj liczbe miast dla ktorej ma byc wygenerowana macierz: "; std::cin >> cities;
		edge = randomGraph(cities);

		edge2 = new int*[cities];
		for (int i = 0; i < cities; i++) {
			edge2[i] = new int[cities];
		}

		for (int i = 0; i < cities; i++) {
			for (int j = 0; j < cities; j++) {
				edge2[i][j] = edge[i][j];
			}
		}
	}

	std::cout << "\nLiczba miast: " << cities << "\n";
	std::cout << "Macierz wag: \n";

	for (int i = 0; i < cities; i++) {
		for (int j = 0; j < cities; j++) {
			std::cout << edge[i][j];
			std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "Wybierz jaki algorytm chcesz wykonac:\n 1.BF\n 2.DP\n 3.B&B\n 0.Wyjscie\n";
	std::cin >> choice;


	while (choice != 0) {

			switch (choice)
			{
			case 1:
			{
				TSPbruteForce TSP(edge, cities);
				TSP.tsp();
			}
			break;

			case 2:
			{
				TSPdp tspdp(edge, cities);
				tspdp.tsp(); 
			}
			break;

			case 3:
			{
				TspBB tspbb(edge, cities);
				tspbb.branchNbound(); 
			}
			break;

			default:
				break;
			}

			if (choice2 == 1) {
				edge = readFile.openFile(cities);
			}
			else {
				edge = randomGraph(cities);
				for (int i = 0; i < cities; i++) {
					for (int j = 0; j < cities; j++) {
						edge[i][j] = edge2[i][j];
					}
				}
			}

			std::cout << "\n";
			std::cout << "\nWybierz jaki algorytm chcesz wykonac:\n 1.BT\n 2.DP\n 3.B&B\n 0.Wyjscie\n";
			std::cin >> choice;
	}
}