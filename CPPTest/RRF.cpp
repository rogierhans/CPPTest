#include "RRF.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <limits>
using namespace std;

 RRF::RRF(SUC uc, bool reduction)
{
	UC = uc;
	Reduction = reduction;
}

 void RRF::AddNew(int h, double startCost)
{
	Fs[h].emplace_back(F(h, startCost, UC));
}

 void RRF::Update(int t)
{
	for (int i = 0; i < Fs[t - 1].size(); i++)
	{
		Fs[t].emplace_back(F(Fs[t - 1][i]));

	}
	for (int i = 0; i < Fs[t].size(); i++)
	{
		Fs[t][i].NextPoints(UC);
		Fs[t][i].IncreasePoints(t, UC);
	}
}

 double RRF::GetBestStop(int h)
{
	double bestStop = numeric_limits<double>::max();

	for (size_t i = 0; i < Fs[h - 1].size(); i++)
	{
		if (h - Fs[h - 1][i].StartIndex >= UC.MinUpTime || Fs[h - 1][i].StartIndex == 0)
		{
			bestStop = min(Fs[h - 1][i].BestEnd(UC), bestStop);
		}
	}
	return bestStop;
}

 double RRF::BestValue(int h)
{
	double bestValue = numeric_limits<double>::max();
	for (auto Z : Fs[h])
	{
		bestValue = min(bestValue, Z.BestValue());
	}
	return bestValue;
}

 void RRF::Print(int t) {
	for (size_t i = 0; i < Fs[t].size(); i++)
	{
		//cout << "F" << i << endl;
		Fs[t][i].Print();
	}
}

 void RRF::FillInDP()
{
	vector<vector<double>> newstop(UC.LagrangeMultipliers.size(), std::vector<double>(UC.MinDownTime, 0.0));
	stop = newstop;
	for (int z = 0; z < UC.LagrangeMultipliers.size(); z++)
	{
		Fs.emplace_back(vector<F>());
	}
	AddNew(0, UC.StartCost);
	for (int h = 1; h < UC.TotalTime; h++)
	{

		stop[h][UC.MinDownTime - 1] = min(stop[h - 1][UC.MinDownTime - 2], stop[h - 1][UC.MinDownTime - 1]);
		for (int t = 1; t < UC.MinDownTime - 1; t++)
		{
			stop[h][t] = stop[h - 1][t - 1];
		}
		stop[h][0] = GetBestStop(h);

		Update(h);
		double bestStart = min(UC.StartCost, UC.StartCost + stop[h - 1][UC.MinDownTime - 1]);
		AddNew(h, bestStart);
	}
}

 double RRF::GetScore()
{


	FillInDP();
	double bestValue = 0;
	for (int tau = 0; tau < UC.MinDownTime; tau++)
	{
		bestValue = min(bestValue, stop[UC.LagrangeMultipliers.size() - 1][tau]);
	}
	bestValue = min(bestValue, BestValue(UC.LagrangeMultipliers.size() - 1));
	return bestValue;
}
