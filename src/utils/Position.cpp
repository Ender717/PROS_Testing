// Included headers
#include "utils/Position.h"

Position::Position(double _x, double _y, double _theta)
{
    x = _x;
    y = _y;
    theta = _theta;
}

Position::Position(double _x, double _y, double _theta, double _xV, double _yV, double _thetaV)
{
    x = _x;
    y = _y;
    theta = _theta;
    xV = _xV;
    yV = _yV;
    thetaV = _thetaV;
}

double Position::getX() const
{
    return x;
}

double Position::getY() const
{
    return y;
}

double Position::getTheta() const
{
    return theta;
}

double Position::getXV() const
{
    return xV;
}

double Position::getYV() const
{
    return yV;
}

double Position::getThetaV() const
{
    return thetaV;
}