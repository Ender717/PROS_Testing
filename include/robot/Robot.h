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
     * The mutex which keeps the robot threadsafe
     */
    static pros::Mutex mutex;

    /**
     * The odometry system for the robot
     */
    static Odometry odometry;

    /**
     * The tank drive for the robot
     */
    static TankDrive tankDrive;

public:
    /**
     * Sets the odometry system of the robot
     * @param _odometry The new odometry system
     */
    static void setOdometry(Odometry& _odometry);

    /**
     * Gets the odometry system of the robot
     * @return The odometry system
     */
    static Odometry& getOdometry();

    /**
     * Sets the tank drive of the robot
     * @param _tankDrive The new tank drive
     */
    static void setTankDrive(TankDrive& _tankDrive);

    /**
     * Gets the tank drive of the robot
     * @return The tank drive
     */
    static TankDrive& getTankDrive();
};

#endif