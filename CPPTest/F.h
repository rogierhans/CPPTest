#pragma once
#include "QuadraticInterval.h"
#include "SUC.h"
struct F
{
public:
	vector<QuadraticInterval> Intervals;
	int StartIndex = 0;
	F(const F& other);
	void Print();
	void IncreasePoints(int t, const SUC& UC);
	F(int startIndex, double startCost, const SUC& UC);
	double BestValue();
	int GetOptimalNode();
	void ShiftLeft(int index, const SUC& UC);
	void ShiftRight(int index, const SUC& UC);
	void Trim();
	double BestEnd(const SUC& UC);
	void NextPoints(const SUC& UC);
};
