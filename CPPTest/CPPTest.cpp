// CPPAOC.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <limits>
#include "QuadraticInterval.h"
#include "SUC.h"
#include "RRF.h"
#include "F.h"
using namespace std;





int main()
{



	SUC suc = SUC::ReadFromFile("C:\\Users\\Rogier\\OneDrive - Universiteit Utrecht\\1UCTest\\GA10\\0.suc");
	suc.PrintStats();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


	for (size_t i = 0; i < 1000; i++)
	{
		RRF rrf(suc, false);
		double score = rrf.GetScore();

	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	return 0;
}

