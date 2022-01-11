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

 F::F(const F& other)
{
	StartIndex = other.StartIndex;
	Intervals.emplace_back(QuadraticInterval{ other.Intervals[0] });
	for (int i = 1; i < other.Intervals.size(); i++)
	{
		if (other.Intervals[i].From != other.Intervals[i].To)
		{
			Intervals.emplace_back(QuadraticInterval{ other.Intervals[i] });
		}
	}

}

 void F::Print()
{

	for (int i = 0; i < Intervals.size(); i++)
	{
		Intervals[i].Print();
	}

}

 void F::IncreasePoints(int t, const SUC& UC)
{
	//cout << "----b4 increase----" << endl;
	//Print(); 
	for (size_t i = 0; i < Intervals.size(); i++)
	{
		Intervals[i].A += UC.A;
		Intervals[i].B += -UC.LagrangeMultipliers[t] + UC.B + UC.BM[t];
		Intervals[i].C += UC.C + UC.CM[t];
		//cout << UC.CM[t] << endl;
	}
	//cout << "Fter increase" << endl;
	//Print();
	//cout << "____________________" << endl;
}

 F::F(int startIndex, double startCost, const SUC& UC)
{
	StartIndex = startIndex;
	if (startIndex == 0)
	{
		Intervals.emplace_back(QuadraticInterval(UC.pMin, UC.pMax, 0, 0, 0, StartIndex));
	}
	else
	{
		Intervals.emplace_back(QuadraticInterval(UC.pMin, UC.SU, startCost, 0, 0, StartIndex));
	}
	//Print();
	IncreasePoints(startIndex, UC);

}

 double F::BestValue()
{
	double bestValue = Intervals[0].ValueMinimum();
	for (int i = 1; i < Intervals.size(); i++)
	{
		bestValue = min(bestValue, Intervals[i].ValueMinimum());
	}
	return bestValue;
}

 int F::GetOptimalNode()
{
	int INDEX = 0;
	double min = Intervals[INDEX].MinimumHack();
	while (min > Intervals[INDEX].To && INDEX < Intervals.size() - 1)
	{
		INDEX++;
		min = Intervals[INDEX].MinimumHack();
	}
	return INDEX;
}

 void F::ShiftLeft(int index, const SUC& UC)
{

	for (int i = 0; i <= index; i++)
	{
		Intervals[i].From = max((double)UC.pMin, Intervals[i].From - UC.RampDown);
		Intervals[i].To = max((double)UC.pMin, Intervals[i].To - UC.RampDown);
		Intervals[i].A = Intervals[i].A + UC.RampDown * Intervals[i].B + UC.RampDown * UC.RampDown * Intervals[i].C;
		Intervals[i].B = Intervals[i].B + UC.RampDown * Intervals[i].C * 2;
	}
}

 void F::ShiftRight(int index, const SUC& UC)
{
	for (int i = index; i < Intervals.size(); i++)
	{
		Intervals[i].From = min((double)UC.pMax, Intervals[i].From + UC.RampUp);
		Intervals[i].To = min((double)UC.pMax, Intervals[i].To + UC.RampUp);
		Intervals[i].A = Intervals[i].A - UC.RampUp * Intervals[i].B + UC.RampUp * UC.RampUp * Intervals[i].C;
		Intervals[i].B = Intervals[i].B - (UC.RampUp * 2 * Intervals[i].C);
	}
}

 void F::Trim()
{
	vector<QuadraticInterval> list;
	for (size_t i = 0; i < Intervals.size(); i++)
	{
		if (Intervals[i].From != Intervals[i].To)
			list.emplace_back(Intervals[i]);
	}
	Intervals = list;
}

 double F::BestEnd(const SUC& UC)
{
	double bestValue = Intervals[0].ValueMinimumRestriced(UC.SD);
	for (int i = 1; i < Intervals.size(); i++)
	{
		if (Intervals[i].From <= UC.SD)
		{
			bestValue = min(bestValue, Intervals[i].ValueMinimumRestriced(UC.SD));
		}
	}
	return bestValue;
}

 void F::NextPoints(const SUC& UC)
{
	int Index = GetOptimalNode();
	double pStar = Intervals[Index].MinimumAtInterval();
	double To = Intervals[Index].To;
	Intervals[Index].To = pStar;
	QuadraticInterval midInterval(max(pStar - UC.RampDown, (double)UC.pMin), min(pStar + UC.RampUp, (double)UC.pMax), Intervals[Index].ValueMinimum(), 0, 0, StartIndex);

	Intervals.insert(Intervals.begin() + Index + 1, midInterval);

	QuadraticInterval rightInterval(Intervals[Index]);
	rightInterval.From = pStar;
	rightInterval.To = To;
	Intervals.insert(Intervals.begin() + Index + 2, rightInterval);
	ShiftLeft(Index, UC);
	ShiftRight(Index + 2, UC);
	Trim();

}