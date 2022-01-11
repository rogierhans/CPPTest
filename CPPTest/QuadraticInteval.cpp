#include "QuadraticInterval.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <limits>
using namespace std;

QuadraticInterval::QuadraticInterval(double from, double to, double a, double b, double c, int zid)
{
	From = from;
	To = to;
	A = a;
	B = b;
	C = c;
	ZID = zid;
}


double QuadraticInterval::IntersectPoint(QuadraticInterval& other, double& Point, double& NextPoint)
{
	if (Point == To)
		return To;
	double p = (A - other.A) / (other.B - B);
	if (From <= p && p <= NextPoint && other.From <= p && p <= NextPoint)
	{
		double val1 = A + B * p;
		double val2 = other.A + other.B * p;
		if (std::abs(val1 - val2) > 0.001)
		{
			cout << "ERROR val1 and val2 differ to much" << endl;
		}
		return p;
	}
	if (To < NextPoint)
	{
		return To;
	}
	cout << "ERROR" << endl;

	return 0;
}

double QuadraticInterval::Minimum()
{
	if (C == 0)
	{
		if (B > 0)
		{
			return From;
		}
		else
		{
			return To;
		}
	}
	return (-B / (2 * C));
}

double QuadraticInterval::MinimumHack()
{
	if (C == 0)
	{
		if (B > 0)
		{
			return -numeric_limits<double>::max();
		}
		else if (B == 0)
		{
			return From;
		}
		else
		{
			return  numeric_limits<double>::max();
		}
	}
	return (-B / (2 * C));

}

double QuadraticInterval::MinimumAtInterval()
{
	if (C == 0)
	{
		if (B > 0)
		{
			return From;
		}
		else
		{
			return To;
		}
	}
	double minimum = (-B / (2 * C));
	if (minimum < From)
	{
		return From;
	}
	else if (minimum > To)
	{
		return To;
	}
	else
	{
		return minimum;
	}
}

bool QuadraticInterval::NonEmptyInterval(double from, double to)
{
	double realFrom = std::max(From, from);
	double realTo = std::min(To, to);
	return realFrom <= realTo;
}

//    double minimum = Math.Min(to, Math.Max(from, MinimumAtInterval())); ;
//    return (minimum, GetValueInt(minimum));
//}

double QuadraticInterval::MinimumAtIntervalRestricted(double max)
{
	double minimum = MinimumAtInterval();
	if (max < From)
	{
		cout << "error" << endl;
		return  numeric_limits<double>::max();
	}
	if (minimum > max)
		return max;
	else
		return minimum;
}

double QuadraticInterval::GetValue(double p)
{

	return A + p * B + (p * p * C);
}

double QuadraticInterval::ValueMinimum()
{
	double minimum = MinimumAtInterval();
	return GetValue(minimum);
}

double QuadraticInterval::ValueMinimumRestriced(double max)
{
	double minimum = MinimumAtIntervalRestricted(max);
	return GetValue(minimum);
}

double QuadraticInterval::GetValueInt(double p)
{
	if (p <= To && From <= To)
		return A + p * B + (p * p * C);
	else
		return  numeric_limits<double>::max();
}

void QuadraticInterval::Print() {
	cout << From << " " << To << " " << A << " " << B << " " << C << " " << endl;
}
