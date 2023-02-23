// Included headers
#include "subsystems/Odometry.h"

void Odometry::runOdometry(void* params)
{
    Odometry* odometry = (Odometry*)params;
    while(true)
    {
        odometry->updatePosition();
        pros::delay(REFRESH_TIME);
    }
}

Odometry::Odometry()
{
    linear = nullptr;
    linearCountsPerInch = 1.0;
    lastLinear = 0.0;

    strafe = nullptr;
    strafeCountsPerInch = 1.0;
    lastStrafe = 0.0;

    inertial = nullptr;
    inertialConstant = 1.0;
    lastInertial = 0.0;

    x = 0.0;
    y = 0.0;
    theta = 0.0;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        xV[i] = 0.0;
        yV[i] = 0.0;
        thetaV[i] = 0.0;
    }
    velocityIndex = 0;

    lastTime = 0;

    running = false;
}

Odometry::Odometry(const Odometry& copy)
{
    if (copy.linear != nullptr)
        linear = new pros::Rotation(*copy.linear);
    else
        linear = nullptr;
    linearCountsPerInch = copy.linearCountsPerInch;
    lastLinear = copy.lastLinear;

    if (copy.strafe != nullptr)
        strafe = new pros::Rotation(*copy.strafe);
    else
        strafe = nullptr;
    strafeCountsPerInch = copy.strafeCountsPerInch;
    lastStrafe = copy.lastStrafe;

    if (copy.inertial != nullptr)
        inertial = new pros::Imu(*copy.inertial);
    else
        inertial = nullptr;
    inertialConstant = copy.inertialConstant;
    lastInertial = copy.lastInertial;

    x = copy.x;
    y = copy.y;
    theta = copy.theta;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        xV[i] = copy.xV[i];
        yV[i] = copy.yV[i];
        thetaV[i] = copy.thetaV[i];
    }
    velocityIndex = copy.velocityIndex;

    lastTime = copy.lastTime;

    running = false;
}

Odometry::~Odometry()
{
    if (linear != nullptr)
        delete linear;
    if (strafe != nullptr)
        delete strafe;
    if (inertial != nullptr)
        delete inertial;
}

double Odometry::getLinear()
{
    double newLinear;

    if (linear != nullptr)
    {
        newLinear = linear->get_position();
        if (std::isnan(newLinear) || std::isinf(newLinear))
            newLinear = lastLinear;
        else
            newLinear *= linearCountsPerInch;
    }
    else
        newLinear = lastLinear;

    return newLinear;
}

double Odometry::getStrafe()
{
    double newStrafe;

    if (strafe != nullptr)
    {
        newStrafe = strafe->get_position();
        if (std::isnan(newStrafe) || std::isinf(newStrafe))
            newStrafe = lastStrafe;
        else
            newStrafe *= strafeCountsPerInch;
    }
    else
        newStrafe = lastStrafe;

    return newStrafe;
}

double Odometry::getInertial()
{
    double newInertial;

    if (inertial != nullptr)
    {
        newInertial = inertial->get_heading();
        if (std::isnan(newInertial) || std::isinf(newInertial))
            newInertial = lastInertial;
        else
            newInertial *= inertialConstant;
    }
    else
        newInertial = lastInertial;

    return newInertial;
}

void Odometry::updatePosition()
{
    // Add a writer to the system
    database.addWriter();

    // Calculate sensor value changes
    double linearChange = getLinear() - lastLinear;
    double strafeChange = getStrafe() - lastStrafe;
    double inertialChange = getInertial() - lastInertial;
    double timeChange = pros::millis()- lastTime;

    // Calculate local movements
    double localX, localY;
    if (inertialChange != 0.0)
    {
        localX = 2.0 * std::sin(inertialChange / 2.0) * (strafeChange / inertialChange);
        localY = 2.0 * std::sin(inertialChange / 2.0) * (linearChange / inertialChange);
    }
    else
    {
        localX = strafeChange;
        localY = linearChange;
    }

    // Calculate global movements
    double averageTheta = theta + (inertialChange / 2.0);
    double xChange = localX * std::sin(averageTheta) + localY * std::cos(averageTheta);
    double yChange = localX * -std::cos(averageTheta) + localY * std::sin(averageTheta);
    double thetaChange = inertialChange;

    // Update position
    x += xChange;
    y += yChange;
    theta += thetaChange;

    // Update velocity - convert to inches per second
    xV[velocityIndex] = (xChange / timeChange) / 1000.0;
    yV[velocityIndex] = (yChange / timeChange) / 1000.0;
    thetaV[velocityIndex] = (thetaChange / timeChange) / 1000.0;

    // Update stored values
    lastLinear += linearChange;
    lastStrafe += strafeChange;
    lastInertial += inertialChange;
    lastTime += timeChange;

    // Remove a writer from the system
    database.removeWriter();
}

void Odometry::setLinear(pros::Rotation& _linear, double _linearCountsPerInch)
{
    if (linear != nullptr)
        delete linear;
    linear = new pros::Rotation(_linear);
    linearCountsPerInch = _linearCountsPerInch;
}

void Odometry::setStrafe(pros::Rotation& _strafe, double _strafeCountsPerInch)
{
    if (strafe != nullptr)
        delete strafe;
    strafe = new pros::Rotation(_strafe);
    strafeCountsPerInch = _strafeCountsPerInch;
}

void Odometry::setInertial(pros::Imu& _inertial, double _inertialConstant)
{
    if (inertial != nullptr)
        delete inertial;
    inertial = new pros::Imu(_inertial);
    inertialConstant = _inertialConstant;
}

void Odometry::initialize()
{
    if (linear != nullptr)
        linear->reset_position();
    if (strafe != nullptr)
        strafe->reset_position();
    if (inertial != nullptr)
    {
        inertial->reset();
        while(inertial->is_calibrating())
            pros::delay(50);
        inertial->tare();
    }
}

void Odometry::start()
{
    if (!running)
    {
        running = true;
        pros::Task* odometryTask = new pros::Task(runOdometry, this, TASK_NAME);
        TaskManager::getInstance()->addTask(odometryTask);
    }
}

void Odometry::stop()
{
    if (running)
    {
        running = false;
        TaskManager::getInstance()->removeTask(TASK_NAME);
    }
}

bool Odometry::isRunning()
{
    return running;
}

void Odometry::setPosition(double _x, double _y, double _theta)
{
    database.addWriter();

    if (linear != nullptr)
        linear->reset_position();
    if (strafe != nullptr)
        strafe->reset_position();
    if (inertial != nullptr)
        inertial->tare();

    x = _x;
    y = _y;
    theta = _theta;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        xV[i] = 0.0;
        yV[i] = 0.0;
        thetaV[i] = 0.0;
    }
    velocityIndex = 0;

    lastLinear = 0.0;
    lastStrafe = 0.0;
    lastInertial = 0.0;
    lastTime = pros::millis();

    database.removeWriter();
}

Position Odometry::getPosition()
{
    database.addReader();

    double xVel = 0.0;
    double yVel = 0.0;
    double thetaVel = 0.0;
    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        xVel += xV[i];
        yVel += yV[i];
        thetaVel += thetaV[i];
    }
    xVel /= VELOCITY_BUFFER;
    yVel /= VELOCITY_BUFFER;
    thetaVel /= VELOCITY_BUFFER;

    Position position(x, y, theta, xVel, yVel, thetaVel);

    database.removeReader();

    return position;
}

Odometry& Odometry::operator=(const Odometry& rhs)
{
    if (linear != nullptr)
        delete linear;
    if (strafe != nullptr)
        delete strafe;
    if (inertial != nullptr)
        delete inertial;

    if (rhs.linear != nullptr)
        linear = new pros::Rotation(*rhs.linear);
    else
        linear = nullptr;
    linearCountsPerInch = rhs.linearCountsPerInch;
    lastLinear = rhs.lastLinear;

    if (rhs.strafe != nullptr)
        strafe = new pros::Rotation(*rhs.strafe);
    else
        strafe = nullptr;
    strafeCountsPerInch = rhs.strafeCountsPerInch;
    lastStrafe = rhs.lastStrafe;

    if (rhs.inertial != nullptr)
        inertial = new pros::Imu(*rhs.inertial);
    else
        inertial = nullptr;
    inertialConstant = rhs.inertialConstant;
    lastInertial = rhs.lastInertial;

    x = rhs.x;
    y = rhs.y;
    theta = rhs.theta;

    for (int i = 0; i < VELOCITY_BUFFER; i++)
    {
        xV[i] = rhs.xV[i];
        yV[i] = rhs.yV[i];
        thetaV[i] = rhs.thetaV[i];
    }
    velocityIndex = rhs.velocityIndex;

    lastTime = rhs.lastTime;

    running = false;

    return *this;
}