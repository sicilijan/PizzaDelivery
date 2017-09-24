/*
 * Deliveries.h
 *
 *  Created on: Sep 16, 2017
 *      Author: janne
 */

#ifndef DELIVERIES_H_
#define DELIVERIES_H_

#include <iostream>
#include <fstream>

class Deliveries {

public:
	Deliveries(int MAX_X, int MAX_Y);
	~Deliveries();

	void readDeliveries(std::istream& is);
	long naiveBest(int &bestX, int &bestY);
	long sumBest(int &bestX, int &bestY);

private:
	int **deliveries;
	int sizeX;
	int sizeY;
	int abs(int x);
	long calculateDistance(int bakeryX, int bakeryY);
	long calculateMinDistance(int sum[], int size, int &best);
};


#endif /* DELIVERIES_H_ */
