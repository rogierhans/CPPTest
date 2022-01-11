#pragma once
struct QuadraticInterval
{
public:
	double From;
	double To;
	double A, B, C;
	int ZID;

	QuadraticInterval(double from, double to, double a, double b, double c, int zid);
	double IntersectPoint(QuadraticInterval& other, double& Point, double& NextPoint);

	double Minimum();

	double MinimumHack();
	double MinimumAtInterval();
	bool NonEmptyInterval(double from, double to);
	//(double, double) MinimumPointAndValue(double from, double to)
	//{
	//    if (To < from || From > to)
	//        return (double.MaxValue, double.MaxValue);


	//    double minimum = Math.Min(to, Math.Max(from, MinimumAtInterval())); ;
	//    return (minimum, GetValueInt(minimum));
	//}
	double MinimumAtIntervalRestricted(double max);

	double GetValue(double p);

	double ValueMinimum();

	double ValueMinimumRestriced(double max);


	double GetValueInt(double p);


	void Print();
};