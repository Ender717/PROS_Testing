// Inclusion guard
#ifndef ODOMETRY_H
#define ODOMETRY_H

// Included headers
#include "main.h"
#include "utils/Position.h"
#include "utils/Database.h"

/**
 * This class manages an odometric position tracking system
 * @author Nathan Sandvig
 */
class Odometry
{
private:
    /**
     * The size of the running velocity average
     */
    static constexpr int VELOCITY_BUFFER = 10;

    /**
     * Database object to make the odometry system thread-safe
     */
    Database database;

    /**
     * The linear tracking wheel configuration
     */
    pros::Rotation* linear;
    double linearConstant;
    double lastLinear;

    /**
     * The strafe tracking wheel configuration
     */
    pros::Rotation* strafe;
    double strafeConstant;
    double lastStrafe;

    /**
     * The inertial sensor configuration
     */
    pros::Imu* inertial;
    double inertialConstant;
    double lastInertial;

    /**
     * The current position data
     */
    double x;
    double y;
    double theta;

    /**
     * The angle at last reset
     */
    double resetTheta;

    /**
     * The current velocity data
     */
    double xV[VELOCITY_BUFFER];
    double yV[VELOCITY_BUFFER];
    double thetaV[VELOCITY_BUFFER];
    int velocityIndex;

    /**
     * The system clock time from the last loop
     */
    int lastTime;

public:
    Odometry();
    Odometry(const Odometry& copy);
    
};

#endif