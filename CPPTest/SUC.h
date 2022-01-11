#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <limits>
using namespace std;
struct SUC
{
public:
	double Objective = 0;
	int TotalTime = 0;
	int pMax = 0;
	int pMin = 0;
	int RampUp = 0;
	int RampDown = 0;
	int SU = 0;
	int SD = 0;
	int MinDownTime = 0;
	int MinUpTime = 0;
	double StartCost = 0;
	double A = 0;
	double B = 0;
	double C = 0;
	vector<double> LagrangeMultipliers;
	vector<double> BM;
	vector<double> CM;

	void PrintStats();
	SUC();

	SUC(double a, double b, double c, double start, int pma, int pmi, int rampUp, int rampDown, int minUpTime, int minDownTime, int su, int sd, int totalTime);

	//	public void SetLM(List<double> LM, double[] bm, double[] cm)
	//	{
	//		LagrangeMultipliers = LM; BM = bm; CM = cm;
	//
	//	}
	static vector<double> split_string_to_vec(const string& s);
	static SUC ReadFromFile(string filename);
};