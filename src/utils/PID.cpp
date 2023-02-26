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

PID::PID(const PID& copy)
{
    kp = copy.kp;
    ki = copy.ki;
    kd = copy.kd;
    sat = copy.sat;
    integral = copy.integral;
    pastError = copy.pastError;
    pastTime = copy.pastTime;
    ffSlope = copy.ffSlope;
    ffOffset = copy.ffOffset;
    target = copy.target;
}

void PID::setSatLimit(double _sat)
{
    mutex.take();
    sat = _sat;
    mutex.give();
}

void PID::setFeedForward(double _ffSlope, double _ffOffset)
{
    mutex.take();
    ffSlope = _ffSlope;
    ffOffset = _ffOffset;
    mutex.give();
}

void PID::setTarget(double _target)
{
    mutex.take();
    target = _target;
    mutex.give();
}

double PID::getValue(double current)
{
    mutex.take();
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
    mutex.give();

    return pValue + iValue + dValue + ffValue;
}

PID& PID::operator=(const PID& rhs)
{
    mutex.take();
    kp = rhs.kp;
    ki = rhs.ki;
    kd = rhs.kd;
    sat = rhs.sat;
    integral = rhs.integral;
    pastError = rhs.pastError;
    pastTime = rhs.pastTime;
    ffSlope = rhs.ffSlope;
    ffOffset = rhs.ffOffset;
    target = rhs.target;
    mutex.give();

    return *this;
}