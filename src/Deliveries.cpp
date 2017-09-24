/*
 * Deliveries.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: janne
 */
#include <iostream>
#include <fstream>
#include <time.h>
#include <limits.h>

#include "Deliveries.h"

using namespace std;

Deliveries::Deliveries(int MAX_X, int MAX_Y) {
		this->sizeX = MAX_X;
		this->sizeY = MAX_Y;
	    deliveries = new int*[sizeX];
	    for (int i = 0; i < sizeX; i++) {
	        deliveries[i] = new int[sizeY];
	    }
}

Deliveries::~Deliveries() {
    for (int i = 0; i < sizeY; i++) {
        delete[] deliveries[i];
    }
    delete[] deliveries;
    deliveries = nullptr;
}

void Deliveries::readDeliveries(istream& is) {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y <  sizeY; y++) {
			is >> deliveries[x][y];
		}
	}
}


int Deliveries::abs(int x) {
	if (x > 0) {
		return x;
	} else {
		return -x;
	}
}


long Deliveries::calculateDistance(int bakeryX, int bakeryY) {
	long totalDistance = 0;
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y <  sizeY; y++) {
			totalDistance += ((abs(bakeryX - x) + abs(bakeryY - y)) * deliveries[x][y]);
		}
	}
	return totalDistance;
}

long Deliveries::calculateMinDistance(int sum[], int size, int &best) {
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


long Deliveries::sumBest(int &bestX, int &bestY) {
	bestX = 0;
	bestY = 0;

	int sumY[sizeX];
	for (int x = 0; x < sizeX; x++) {
		sumY[x] = 0;
		for (int y = 0; y < sizeY; y++) {
			sumY[x] += deliveries[x][y];
		}

	}

	int sumX[sizeY];
	for (int y = 0; y < sizeY; y++) {
		sumX[y] = 0;
		for (int x = 0; x < sizeX; x++) {
			sumX[y] += deliveries[x][y];
		}
	}

	long xDistance = calculateMinDistance(sumY, sizeX, bestX);
	long yDistance = calculateMinDistance(sumX, sizeY, bestY);

	return xDistance + yDistance;
}

long Deliveries::naiveBest(int &bestX, int &bestY) {
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
