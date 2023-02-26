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
    static constexpr int REFRESH_TIME = 20;

    /**
     * The size of the velocity tracking arrays
     */
    static constexpr int VELOCITY_BUFFER = 10;

    /**
     * The mutex to keep the tank drive thread safe
     */
    pros::Mutex mutex;

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
     * Whether the tank drive is running or not
     */
    bool running;

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
    /**
     * Default constructor
     */
    TankDrive();

    /**
     * Copy constructor
     * @param copy The TankDrive being copied
     */
    TankDrive(const TankDrive& copy);

    /**
     * Adds a motor to the left side of the drive
     * @param motor The motor being added
     */
    void addLeftMotor(pros::Motor& motor);

    /**
     * Adds a motor to the right side of the drive
     * @param motor The motor being added
     */
    void addRightMotor(pros::Motor& motor);

    /**
     * Adds a piston to the transmission
     * @param piston The piston being added
     */
    void addTransmissionPiston(pros::ADIDigitalOut& piston);

    /**
     * Sets the configuration for the transmission
     * @param _transmissionRatio The gear ratio on the transmission
     * @param _lowGear Whether the transmission is in low gear or not
     */
    void setTransmissionData(double _transmissionRatio, bool _lowGear);

    /**
     * Sets the PID controller for the left side of the drive in high gear
     * @param _leftHighPID The PID controller
     */
    void setLeftHighPID(PID& _leftHighPID);

    /**
     * Sets the PID controller for the left side of the drive in low gear
     * @param _leftLowPID The PID controller
     */
    void setLeftLowPID(PID& _leftLowPID);

    /**
     * Sets the PID controller for the right side of the drive in high gear
     * @param _rightHighPID The PID controller
     */
    void setRightHighPID(PID& _rightHighPID);

    /**
     * Sets the PID controller for the right side of the drive in low gear
     * @param _rightLowPID The PID controller
     */
    void setRightLowPID(PID& _rightLowPID);

    /**
     * Sets the encoder counts per inch of travel
     * @param _countsPerInch The number of counts per inch of travel
     */
    void setCountsPerInch(double _countsPerInch);

    /**
     * Initializes the drive
     */
    void initialize();

    /**
     * Checks if the tank drive is running
     * @return True if the tank drive is running, false if not
     */
    bool isRunning();

    /**
     * Sets the velocity of each side of the drive
     * @param leftV The velocity for the left side of the drive
     * @param rightV The velocity for the right side of the drive
     */
    void setVelocity(double leftV, double rightV);

    /**
     * Gets the velocity of the left side of the drive
     * @return The velocity of the left side of the drive
     */
    double getLeftVelocity();

    /**
     * Gets the velocity of the right side of hte drive
     * @return The velocity of the right side of the drive
     */
    double getRightVelocity();

    /**
     * Switches between low and high gears
     */
    void switchGear();

    /**
     * Checks if the transmission is in low gear
     * @return True if the transmission is in low gear, false if not
     */
    bool isLowGear();

    /**
     * Assigment uperator for TankDrive
     * @param rhs The TankDrive on the right hand side of the operator
     * @return This TankDrive with the assigned values
     * */
    TankDrive& operator=(const TankDrive& rhs);
};

#endif