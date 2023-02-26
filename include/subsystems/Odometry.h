// Inclusion guard
#ifndef ODOMETRY_H
#define ODOMETRY_H

// Included headers
#include "main.h"
#include "utils/Utilities.h"

/**
 * This class manages an odometric position tracking system
 * @author Nathan Sandvig
 */
class Odometry
{
private:
    /**
     * The name of the task for running Odometry
     */
    static constexpr char TASK_NAME[20] = "Odometry Task";

    /**
     * The number of milliseconds to wait in-between each update
     */
    static constexpr int REFRESH_TIME = 10;

    /**
     * The size of the running velocity average
     */
    static constexpr int VELOCITY_BUFFER = 10;

    /**
     * Mutex to make the odometry system thread-safe
     */
    pros::Mutex mutex;

    /**
     * The linear tracking wheel configuration
     */
    pros::Rotation* linear;
    double linearCountsPerInch;
    double lastLinear;

    /**
     * The strafe tracking wheel configuration
     */
    pros::Rotation* strafe;
    double strafeCountsPerInch;
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

    /**
     * Runs the system by updating it in a loop
     * Must be static for task
     * @param params The input parameters for the task
     */
    static void runOdometry(void* params);

    /**
     * Gets the current linear position in inches
     * @return The linear position in inches
     */
    double getLinear();

    /**
     * Gets the current strafe position in inches
     * @return The strafe position in inches
     */
    double getStrafe();

    /**
     * Gets the current inertial position in radians
     * @return The inertial position in radians
     */
    double getInertial();

    /**
     * Updates the position of the system
     */
    void updatePosition();

public:
    /**
     * Default constructor
     */
    Odometry();

    /**
     * Copy constructor
     * @param copy The odometry system being copied
     */
    Odometry(const Odometry& copy);

    /**
     * Destructor
     */
    ~Odometry();

    /**
     * Sets the linear tracking sensor configuration
     * @param _linear The rotation sensor for the tracking wheel
     * @param _linearCountsPerInch The number of counts per inch of travel
     */
    void setLinear(pros::Rotation& _linear, double _linearCountsPerInch);

    /**
     * Sets the strafe tracking sensor configuration
     * @param _strafe The rotation sensor for the tracking wheel
     * @param _strafeCountsPerInch The number of counts per inch of travel
     */
    void setStrafe(pros::Rotation& _strafe, double _strafeCountsPerInch);

    /**
     * Sets the inertial sensor configuration
     * @param _inertial The inertial sensor
     * @param _inertialConstant The tuning constant for the sensor
     */
    void setInertial(pros::Imu& _inertial, double _inertialConstant);

    /**
     * Initializes the system
     */
    void initialize();

    /**
     * Sets the position of the system
     * @param _x The new x-coordinate
     * @param _y The new y-coordinate
     * @param _theta The new angle
     */
    void setPosition(double _x, double _y, double _theta);

    /**
     * Gets the position of the system
     * @return The position of the system
     */
    Position getPosition();

    /**
     * Assignment operator overload
     * @param rhs The odometry system on the right hand side of the operator
     * @return This odometry system with the assigned values
     */
    Odometry& operator=(const Odometry& rhs);
};

#endif