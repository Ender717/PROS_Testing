// Included headers
#include "robot/Robot.h"

Robot* Robot::instance = nullptr;

Robot::Robot()
{

}

Robot* Robot::getInstance()
{
    if (instance == nullptr)
        instance = new Robot;
    return instance;
}

void Robot::setOdometry(Odometry _odometry)
{
    if (odometry != nullptr)
        delete odometry;
    odometry = new Odometry(_odometry);
}

Odometry* Robot::getOdometry()
{
    return odometry;
}