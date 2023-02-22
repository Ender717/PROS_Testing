// Included headers
#include "utils/PID.h"

PID::PID()
{
    kp = 0.0;
    ki = 0.0;
    kd = 0.0;
    sat = 0.0;
    integral = 0.0;
    pastError = 0.0;
    pastTime = 0.0;
    ffSlope = 0.0;
    ffOffset = 0.0;
    target = 0.0;
}

PID::PID(double _kp, double _ki, double _kd)
{
    kp = _kp;
    ki = _ki;
    kd = _kd;
    sat = 0.0;
    integral = 0.0;
    pastError = 0.0;
    pastTime = 0.0;
    ffSlope = 0.0;
    ffOffset = 0.0;
    target = 0.0;
}

void PID::setSatLimit(double _sat)
{
    sat = _sat;
}

void PID::setFeedForward(double _ffSlope, double _ffOffset)
{
    ffSlope = _ffSlope;
    ffOffset = _ffOffset;
}

double PID::getValue(double current)
{
    double error = target - current;
    int time = pros::millis();

    double pValue = kp * error;

    integral += error * (time - pastTime);
    if (std::abs(integral) > std::abs(sat / ki))
        integral = sat / ki * sign<double>(integral);
    double iValue = ki * integral;

    double dValue = kd * (error - pastError) / (time - pastTime);

    double ffValue = (ffSlope * target) + (ffOffset * sign<double>(target));

    pastError = error;
    pastTime = time;

    return pValue + iValue + dValue + ffValue;
}