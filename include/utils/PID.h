// Inclusion guard
#ifndef PID_H
#define PID_H

// Included headers
#include "main.h"
#include "Functions.h"

/**
 * This class manages a PID controller
 * @author Nathan Sandvig
 */
class PID
{
private:
    /**
     * The mutex to keep the PID controller threadsafe
     */
    pros::Mutex mutex;

    /**
     * Control constants
     */
    double kp;
    double ki;
    double kd;

    /**
     * Saturation limit for integral
     */
    double sat;

    /**
     * Accumulated error
     */
    double integral;

    /**
     * The error value in the past loop
     */
    double pastError;

    /**
     * The system time in the past loop
     */
    int pastTime;

    /**
     * Feed forward control values
     */
    double ffSlope;
    double ffOffset;

    /**
     * The target for the PID controller
     */
    double target;

public:
    /**
     * Default constructor
     */
    PID();

    /**
     * Parameterized constructor
     * @param _kp The proportional control constant
     * @param _ki The integral control constant
     * @param _kd The derivative control constant
     */
    PID(double _kp, double _ki, double _kd);

    /**
     * Copy constructor
     * @param copy The PID controller being copied
     */
    PID(const PID& copy);

    /**
     * Sets the saturation limit for the integral
     * @param _sat The new saturation limit
     */
    void setSatLimit(double _sat);

    /**
     * Sets the feed forward control values
     * @param _ffSlope The slope for the feed forward control
     * @param _ffOffset The offset for the feed forward control
     */
    void setFeedForward(double _ffSlope, double _ffOffset);

    /**
     * Sets the target of the controller
     * @param _target The new target
     */
    void setTarget(double _target);

    /**
     * Gets the control value
     * @param current The current system value
     * @return The calculated control value
     */
    double getValue(double current);

    /**
     * Assignment operator overload for PID
     * @param rhs The PID on the right hand side of the operator
     * @return This PID controller with the assigned values
     */
    PID& operator=(const PID& rhs);
};

#endif