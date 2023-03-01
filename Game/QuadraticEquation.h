#ifndef QUADRATICEQUATION_H
#define QUADRATICEQUATION_H

using namespace std;

struct QEResults
{
	int resultsNumber;
	double x1, x2;

	QEResults()
	{
		resultsNumber = 0;
		x1, x2 = 0;
	}
	QEResults(double x1)
	{
		resultsNumber = 1;
		this->x1 = x1;
		x2 = x1;
	}
	QEResults(double x1, double x2)
	{
		resultsNumber = 2;
		if (x1 < x2)
		{
			this->x1 = x1;
			this->x2 = x2;
		}
		else
		{
			this->x1 = x2;
			this->x2 = x1;
		}
	}
};

class QuadraticEquation
{
private:
	double a, b, c;
	double delta;
	QEResults result;

public:
	QuadraticEquation();
	QuadraticEquation(double a2, double b2, double c2);
	void setA(float a2);
	void setB(float b2);
	void setC(float c2);
	void fixResult();
	double getDelta() const;
	QEResults getResult() const;
};

void printQEResults(const QEResults &results, const char *c = "\n");

#endif