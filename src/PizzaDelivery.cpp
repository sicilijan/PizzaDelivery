//============================================================================
// Name        : PizzaDelivery.cpp
// Author      : Jan Lundkvist
// Version     :
// Copyright   : No copyright
// Description : Pizza Delivery, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#include "Deliveries2.h"

using namespace std;

#define TIMING

#ifdef TIMING
#define	INIT_TIMER  auto start = chrono::high_resolution_clock::now();
#define START_TIMER	start = chrono::high_resolution_clock::now();
#define STOP_TIMER  auto time = chrono::duration_cast<chrono::microseconds>(\
						  chrono::high_resolution_clock::now()-start).count();
#define COUT_TIMER cout << "Execution time: " << float(time) / 1000.0 << " ms " << endl;
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER
#define COUT_TIMER
#endif

static void show_usage(string name)
{
    cerr << "Usage: " << name << " noRows noColumns <data file> \n"
         << "\tIf no data file is entered the program will read from stdin \n"
		 << "Options:\n"
         << "\t-h,--help\t\tShow this message\n"
		 << endl;
}

int main(int argc, char* argv[]) {
	string dataFile;
    int rows, columns;

    string arg = argv[1];
    if ((arg == "-h") || (arg == "--help") || (argc < 3 || argc > 4)) {
    	show_usage(argv[0]);
    	return 0;
    }

    istringstream rowsSS( argv[1] );
    istringstream colsSS( argv[2] );

    if (!(rowsSS >> rows)) {
    	cerr << "First argument, noRows, should be an integer: " << argv[1] << endl;
    	return 1;
    }
    if (!(colsSS >> columns)) {
    	cerr << "Second argument, noColumns, should be an integer: " << argv[2] << endl;
    	return 1;
    }

    if (argc == 4) {
    	dataFile = argv[3];
    }

	Deliveries2 deliveries(rows, columns);
	if (!dataFile.empty()) {
		ifstream myFile(dataFile, ios_base::in);
	    if (!myFile.is_open()) {
	    	cerr << "Could not open file" << dataFile << endl;
	    	return 1;
	    }
	    deliveries.readDeliveries(myFile);
	} else {
		deliveries.readDeliveries(cin);
	}
	int bestX, bestY;
	long minDistance;

//	clock_t start, stop;
//	start = clock();
	INIT_TIMER
	START_TIMER
	minDistance = deliveries.sumBest(bestX, bestY);
	STOP_TIMER
//	stop = clock();
//	float milliSeconds = float (stop-start)/CLOCKS_PER_SEC * 1000;
	cout << minDistance << " blocks" << endl;
	cout << "(" << bestX << "," << bestY << ")" << endl;
	COUT_TIMER

	return 0;
}
