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
     * The name of the task for running Tank Drive updates
     */
    static constexpr char TASK_NAME[20] = "Tank Drive Task";

    /**
     * The number of milliseconds to wait in-between each update
     */
    static constexpr int REFRESH_TIME = 10;

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
     * The transmission data
     */
    PistonGroup transmission;
    double transmissionRatio;
    bool lowGear;

    /**
     * The PID controllers for each side of the drive
     */
    PID leftHighPID;
    PID leftLowPID;
    PID rightHighPID;
    PID rightLowPID;

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
    void addLeftMotor(pros::Motor motor);
    void addRightMotor(pros::Motor motor);
    void addTransmissionPiston(pros::ADIDigitalOut piston);
    void setTransmissionRatio(double _transmissionRatio);
    void setLeftHighPID(PID _leftHighPID);
    void setLeftLowPID(PID _leftLowPID);
    void setRightHighPID(PID _rightHighPID);
    void setRightLowPID(PID _rightLowPID);
    void setCountsPerInch(double _countsPerInch);
    void initialize();
    void start();
    void stop();
    void setVelocity(double leftV, double rightV);
    double getLeftVelocity();
    double getRightVelocity();
    void switchGear();
    bool isLowGear();
    TankDrive& operator=(const TankDrive& rhs);
};

#endif