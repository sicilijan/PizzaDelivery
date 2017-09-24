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

class Deliveries2 {

public:
	Deliveries2(int MAX_X, int MAX_Y);
	~Deliveries2();

	void readDeliveries(std::istream& is);
	long naiveBest(int &bestX, int &bestY);
	long sumBest(int &bestX, int &bestY);

private:
	unsigned char *deliveries;
	int sizeX;
	int sizeY;
	inline int index(int x, int y) { return x * sizeY + y; }
	inline int abs(int x) {	if (x > 0) return x; return -x; }

	long calculateDistance(int bakeryX, int bakeryY);
	long calculateMinDistance(int sum[], int size, int &best);
};


#endif /* DELIVERIES_H_ */
