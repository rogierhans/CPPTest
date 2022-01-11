#pragma once
#include "F.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <limits>
using namespace std;

class RRF
{
public:
	bool Reduction = true;
	vector<vector<F>> Fs;

	SUC UC;

	RRF(SUC uc, bool reduction);

	void AddNew(int h, double startCost);

	void Update(int t);

	double GetBestStop(int h);


	double BestValue(int h);

	void Print(int t);

	vector<vector< double>> stop;
	void FillInDP();
	double GetScore();

};