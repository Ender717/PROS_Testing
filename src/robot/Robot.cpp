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