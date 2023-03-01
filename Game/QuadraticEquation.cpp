#include"QuadraticEquation.h"

#define _USE_MATH_DEFINES

#include<cmath>
#include<iostream>

QuadraticEquation::QuadraticEquation()
{
	a, b, c, delta = 0;
}

QuadraticEquation::QuadraticEquation(double a2, double b2, double c2)
{
	a = a2;
	b = b2;
	c = c2;
	fixResult();
}

void QuadraticEquation::setA(float a2)
{
	a = a2;
	fixResult();
}

void QuadraticEquation::setB(float b2)
{
	b = b2;
	fixResult();
}

void QuadraticEquation::setC(float c2)
{
	c = c2;
	fixResult();
}

void QuadraticEquation::fixResult()
{
	if (a == 0)
	{
		result = QEResults(-c / b);
		return;
	}

	delta = b * b - 4 * a * c;

	if (delta > 0)
	{
		double pw = sqrt(delta);
		result = QEResults((-b + pw) / (2 * a), (-b - pw) / (2 * a));
	}
	else if (delta == 0)
		result = QEResults(-b / (2 * a));
	else
		result = QEResults();
}

double QuadraticEquation::getDelta() const
{
	return delta;
}

QEResults QuadraticEquation::getResult() const
{
	return result;
}

void printQEResults(const QEResults &results, const char *c)
{
	switch (results.resultsNumber)
	{
	case 0:
		printf("No results%s", c);
		break;
	case 1:
		printf("xw = %f%s", results.x1, c);
		break;
	case 2:
		printf("x1 = %f\nx2 = %f%s", results.x1, results.x2, c);
		break;
	}
}