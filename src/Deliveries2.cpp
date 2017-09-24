/*
 * Deliveries.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: janne
 */
#include "Deliveries2.h"

#include <iostream>
#include <fstream>
#include <time.h>
#include <limits.h>

using namespace std;

Deliveries2::Deliveries2(int MAX_X, int MAX_Y) {
		this->sizeX = MAX_X;
		this->sizeY = MAX_Y;
	    deliveries = new unsigned char[sizeX * sizeY];
}

Deliveries2::~Deliveries2() {
    delete[] deliveries;
    deliveries = nullptr;
}

void Deliveries2::readDeliveries(istream& is) {
	int a = 0;
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y <  sizeY; y++) {
			is >> a;
			deliveries[index(x,y)] = a;
		}
	}
}

long Deliveries2::calculateDistance(int bakeryX, int bakeryY) {
	long totalDistance = 0;
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y <  sizeY; y++) {
			totalDistance += ((abs(bakeryX - x) + abs(bakeryY - y)) * deliveries[index(x,y)]);
		}
	}
	return totalDistance;
}

long Deliveries2::calculateMinDistance(int sum[], int size, int &best) {
	long minDistance = LONG_MAX;
	for (int i = 0; i < size; i++) {
		long distance = 0;
		for (int j = 0; j < size; j++) {
			distance += abs(j-i) * sum[j];
		}
		if (distance < minDistance) {
			best = i;
			minDistance = distance;
		}
	}
	return minDistance;
}


long Deliveries2::sumBest(int &bestX, int &bestY) {
	bestX = 0;
	bestY = 0;

	int sumY[sizeX];
	for (int x = 0; x < sizeX; x++) {
		sumY[x] = 0;
		for (int y = 0; y < sizeY; y++) {
			sumY[x] += deliveries[index(x,y)];
		}

	}

	int sumX[sizeY];
	for (int y = 0; y < sizeY; y++) {
		sumX[y] = 0;
		for (int x = 0; x < sizeX; x++) {
			sumX[y] += deliveries[index(x,y)];
		}
	}

	long xDistance = calculateMinDistance(sumY, sizeX, bestX);
	long yDistance = calculateMinDistance(sumX, sizeY, bestY);

	return xDistance + yDistance;
}

long Deliveries2::naiveBest(int &bestX, int &bestY) {
	long minDistance = calculateDistance(0,0);
	bestX = 0;
	bestY = 0;
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y <  sizeY; y++) {
			long distance = calculateDistance(x, y);
			if (distance < minDistance) {
				minDistance = distance;
				bestX = x;
				bestY = y;
			}
		}
	}
	return minDistance;
}
