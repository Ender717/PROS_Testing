// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included headers
#include "subsystems/Subsystems.h"

/**
 * This class manages a singleton robot
 * @author Nathan Sandvig
 */
class Robot
{
private:
    /**
     * The singleton instance of the robot
     */
    static Robot* instance;

    /**
     * The odometry system for the robot
     */
    Odometry* odometry;

    /**
     * Private constructor to prevent uncontrolled construction
     */
    Robot();

public:
    /**
     * Remove the copy constructor
     */
    Robot(const Robot& copy) = delete;

    /**
     * Remove the assignment operator
     */
    Robot& operator=(const Robot& rhs) = delete;

    /**
     * Gets the singleton instance of the robot
     */
    static Robot* getInstance();

    /**
     * Sets the odometry system of the robot
     * @param _odometry The new odometry system
     */
    void setOdometry(Odometry _odometry);

    /**
     * Gets the odometry system of the robot
     * @return The odometry system
     */
    Odometry* getOdometry();
};

#endif