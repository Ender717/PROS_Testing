// Included headers
#include "robot/Robot.h"

void Robot::setOdometry(Odometry& _odometry)
{
    mutex.take();
    odometry = _odometry;
    mutex.give();
}

Odometry& Robot::getOdometry()
{
    mutex.take();
    Odometry& result = odometry;
    mutex.give();
    return result;
}

void Robot::setTankDrive(TankDrive& _tankDrive)
{
    mutex.take();
    tankDrive = _tankDrive;
    mutex.give();
}

TankDrive& Robot::getTankDrive()
{
    mutex.take();
    TankDrive& result = tankDrive;
    mutex.give();
    return result;
}