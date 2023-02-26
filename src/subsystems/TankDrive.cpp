// Inclusion giard
#include "subsystems/TankDrive.h"

void TankDrive::runTankDrive(void* params)
{
    TankDrive* tankDrive = (TankDrive*)params;
    while(true)
    {
        tankDrive->update();
        pros::delay(REFRESH_TIME);
    }
}

TankDrive::TankDrive()
{
    transmissionRatio = 1.0;
    lowGear = false;
    countsPerInch = 1.0;
    lastLeft = 0.0;
    lastRight = 0.0;
    lastTime = 0;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        leftV[i] = 0.0;
        rightV[i] = 0.0;
    }
    velocityIndex = 0;

    running = false;
}

TankDrive::TankDrive(const TankDrive& copy)
{
    leftMotors = copy.leftMotors;
    rightMotors = copy.rightMotors;
    transmission = copy.transmission;
    transmissionRatio = copy.transmissionRatio;
    lowGear = copy.lowGear;
    leftHighPID = copy.leftHighPID;
    leftLowPID = copy.leftLowPID;
    rightHighPID = copy.rightHighPID;
    rightLowPID = copy.rightLowPID;
    countsPerInch = copy.countsPerInch;
    lastLeft = copy.lastLeft;
    lastRight = copy.lastRight;
    lastTime = copy.lastTime;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        leftV[i] = copy.leftV[i];
        rightV[i] = copy.rightV[i];
    }
    velocityIndex = copy.velocityIndex;

    running = false;
}

double TankDrive::leftVelocity()
{
    double velocity = 0.0;
    for (int i = 0; i < VELOCITY_BUFFER; i++)
        velocity += leftV[i];
    return velocity / VELOCITY_BUFFER;
}

double TankDrive::rightVelocity()
{
    double velocity = 0.0;
    for (int i = 0; i < VELOCITY_BUFFER; i++)
        velocity += rightV[i];
    return velocity / VELOCITY_BUFFER;
}

void TankDrive::update()
{
    mutex.take();

    double newLeft = leftMotors.get_position();
    double newRight = rightMotors.get_position();
    int newTime = pros::millis();
    double leftPower = 0.0;
    double rightPower = 0.0;

    double leftVelocity = (newLeft - lastLeft) / (newTime - lastTime) / 1000.0 / countsPerInch;
    double rightVelocity = (newRight - lastRight) / (newTime - lastTime) / 1000.0 / countsPerInch;

    if (lowGear)
    {
        leftV[velocityIndex] = leftVelocity / transmissionRatio;
        rightV[velocityIndex] = rightVelocity / transmissionRatio;
        leftPower = leftLowPID.getValue(getLeftVelocity());
        rightPower = rightLowPID.getValue(getRightVelocity());
    }
    else
    {
        leftV[velocityIndex] = leftVelocity;
        rightV[velocityIndex] = rightVelocity;
        leftPower = leftHighPID.getValue(getLeftVelocity());
        rightPower = rightHighPID.getValue(getRightVelocity());
    }

    leftMotors.move_voltage(leftPower);
    rightMotors.move_voltage(rightPower);
    lastLeft = newLeft;
    lastRight = newRight;
    lastTime = newTime;
    velocityIndex = (velocityIndex + 1) % VELOCITY_BUFFER;

    mutex.give();
}

void TankDrive::addLeftMotor(pros::Motor& motor)
{
    mutex.take();
    leftMotors.add_motor(motor);
    mutex.give();
}

void TankDrive::addRightMotor(pros::Motor& motor)
{
    mutex.take();
    rightMotors.add_motor(motor);
    mutex.give();
}

void TankDrive::addTransmissionPiston(pros::ADIDigitalOut& piston)
{
    mutex.take();
    transmission.add_piston(piston);
    mutex.give();
}

void TankDrive::setTransmissionData(double _transmissionRatio, bool _lowGear)
{
    mutex.take();
    transmissionRatio = _transmissionRatio;
    lowGear = _lowGear;
    mutex.give();
}

void TankDrive::setLeftHighPID(PID& _leftHighPID)
{
    mutex.take();
    leftHighPID = _leftHighPID;
    mutex.give();
}

void TankDrive::setLeftLowPID(PID& _leftLowPID)
{
    mutex.take();
    leftLowPID = _leftLowPID;
    mutex.give();
}

void TankDrive::setRightHighPID(PID& _rightHighPID)
{
    mutex.take();
    rightHighPID = _rightHighPID;
    mutex.give();
}

void TankDrive::setRightLowPID(PID& _rightLowPID)
{
    mutex.take();
    rightLowPID = _rightLowPID;
    mutex.give();
}

void TankDrive::setCountsPerInch(double _countsPerInch)
{
    mutex.take();
    countsPerInch = _countsPerInch;
    mutex.give();
}

void TankDrive::initialize()
{
    mutex.take();
    leftMotors.tare_position();
    rightMotors.tare_position();
    pros::Task tankDriveTask(runTankDrive, this, TASK_NAME);
    mutex.give();
}

void TankDrive::setVelocity(double leftV, double rightV)
{
    mutex.take();
    leftHighPID.setTarget(leftV);
    leftLowPID.setTarget(leftV);
    rightHighPID.setTarget(rightV);
    rightLowPID.setTarget(rightV);
    mutex.give();
}

double TankDrive::getLeftVelocity()
{
    mutex.take();
    double velocity = leftVelocity();
    mutex.give();
    return velocity;
}

double TankDrive::getRightVelocity()
{
    mutex.take();
    double velocity = rightVelocity();
    mutex.give();
    return velocity;
}

void TankDrive::switchGear()
{
    mutex.take();
    lowGear = !lowGear;
    transmission.toggle();
    mutex.give();
}

bool TankDrive::isLowGear()
{
    mutex.take();
    bool result = lowGear;
    mutex.give();
    return result;
}

TankDrive& TankDrive::operator=(const TankDrive& rhs)
{
    mutex.take();

    leftMotors = rhs.leftMotors;
    rightMotors = rhs.rightMotors;
    transmission = rhs.transmission;
    transmissionRatio = rhs.transmissionRatio;
    lowGear = rhs.lowGear;
    leftHighPID = rhs.leftHighPID;
    leftLowPID = rhs.leftLowPID;
    rightHighPID = rhs.rightHighPID;
    rightLowPID = rhs.rightLowPID;
    countsPerInch = rhs.countsPerInch;
    lastLeft = rhs.lastLeft;
    lastRight = rhs.lastRight;
    lastTime = rhs.lastTime;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        leftV[i] = rhs.leftV[i];
        rightV[i] = rhs.rightV[i];
    }
    velocityIndex = rhs.velocityIndex;

    mutex.give();

    return *this;
}