
#include "SUC.h";
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <limits>
using namespace std;
 SUC::SUC()
{
}

 SUC::SUC(double a, double b, double c, double start, int pma, int pmi, int rampUp, int rampDown, int minUpTime, int minDownTime, int su, int sd, int totalTime)
{

	pMax = pma;
	pMin = pmi;
	SU = su;
	SD = sd;
	RampUp = max(rampUp, 1);
	RampDown = max(rampDown, 1);
	MinDownTime = minDownTime;
	MinUpTime = minUpTime;
	StartCost = start;
	A = a;
	B = b;
	C = c;
	TotalTime = totalTime;
}

//	public void SetLM(List<double> LM, double[] bm, double[] cm)
//	{
//		LagrangeMultipliers = LM; BM = bm; CM = cm;
//
//	}

 vector<double> SUC::split_string_to_vec(const string& s) {
	vector<double> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, '\t')) {
		result.emplace_back(stod(item));
	}

	return result;
}

 SUC SUC::ReadFromFile(string filename)
{
	SUC suc;

	fstream newfile;
	vector<string> lines;
	newfile.open(filename, ios::in);
	if (newfile.is_open()) {
		string tp;
		while (getline(newfile, tp)) {
			lines.emplace_back(tp);
		}
	}
	int i = 0;
	suc.Objective = stod(lines[i++]);
	suc.TotalTime = stoi(lines[i++]);
	suc.pMax = stoi(lines[i++]);
	suc.pMin = stoi(lines[i++]);
	suc.RampUp = stoi(lines[i++]);
	suc.RampDown = stoi(lines[i++]);
	suc.SU = stoi(lines[i++]);
	suc.SD = stoi(lines[i++]);
	suc.MinDownTime = stoi(lines[i++]);
	suc.MinUpTime = stoi(lines[i++]);
	suc.StartCost = stod(lines[i++]);
	suc.A = stod(lines[i++]);
	suc.B = stod(lines[i++]);
	suc.C = stod(lines[i++]);
	suc.LagrangeMultipliers = split_string_to_vec(lines[i++]);
	suc.BM = split_string_to_vec(lines[i++]);
	suc.CM = split_string_to_vec(lines[i++]);
	return suc;
}
 void SUC::PrintStats()
 {
	 cout << Objective << " " << pMin << " " << pMax << " " << RampUp << " " << RampDown << " " << SU << " " << SD << " " << MinUpTime << " " << MinDownTime << endl;
	 //for (size_t t = 0; t < CM.size(); t++)
	 //{
	 //	cout << CM[t] << endl;
	 //}

 }