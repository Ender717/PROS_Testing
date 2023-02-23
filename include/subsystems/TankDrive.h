// Inclusion guard
#ifndef TANK_DRIVE_H
#define TANK_DRIVE_H

// Included headers
#include "main.h"
#include "utils/Utilities.h"

/**
 * This class manages a tank drive subsystem
 * @author Nathan Sandvig
 */
class TankDrive
{
private:
    /**
     * The size of the velocity tracking arrays
     */
    static constexpr int VELOCITY_BUFFER = 10;

    /**
     * The motors on each side of the drive
     */
    MotorGroup leftMotors;
    MotorGroup rightMotors;

    /**
     * The PID controllers for each side of the drive
     */
    PID leftHighPID;
    PID leftLowPID;
    PID rightHighPID;
    PID rightLowPID;

    /**
     * The transmission data
     */
    pros::ADIDigitalOut* transmission;
    double transmissionRatio;
    bool lowGear;

    /**
     * The number of encoder counts per inch of travel
     */
    double countsPerInch;

    /**
     * The last position of the drive
     */
    double lastLeft;
    double lastRight;
    int lastTime;

    /**
     * Velocity tracking arrays
     */
    double leftV[VELOCITY_BUFFER];
    double rightV[VELOCITY_BUFFER];
    int velocityIndex;

    /**
     * Runs the tank drive
     * Must be static with void* parameters for task
     * @param params The input parameters
     */
    static void runTankDrive(void* params);

    /**
     * Updates the tank drive
     */
    void update();

public:
    TankDrive();
    TankDrive(const TankDrive& copy);
    ~TankDrive();
};

#endif