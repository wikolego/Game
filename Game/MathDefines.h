#ifndef MATHDEFINES_H
#define MATHDEFINES_H

#define M_PIF 3.14159265358979323846f

#define COS(R) cos((R) * M_PIF / 180.f)
#define SIN(R) sin((R) * M_PIF / 180.f)
#define TAN(R) tan((R) * M_PIF / 180.f)
#define ACOS(R) (acos(R) * 180.f / M_PIF)
#define ATAN(R) (atan(R) * 180.f / M_PIF)
#define ATAN2(X, Y) (atan2(Y, X) * 180.f / M_PIF)

#define DIRECTION(X1, Y1, X2, Y2) (ATAN2((X2) - (X1), (Y2) - (Y1)) + 360.f * ((Y2 - Y1) < 0.f))
#define DISTANCE(X1, Y1, X2, Y2) sqrt(((X2) - (X1)) * ((X2) - (X1)) + ((Y2) - (Y1)) * ((Y2) - (Y1)))
#define DISTANCE2(DIFFERENCE_X, DIFFERENCE_Y) sqrt((DIFFERENCE_X) * (DIFFERENCE_X) + (DIFFERENCE_Y) * (DIFFERENCE_Y));

#endif