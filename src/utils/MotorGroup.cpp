// Included headers
#include "utils/MotorGroup.h"
#include "pros/motors.h"

MotorGroup::MotorGroup()
{

}

MotorGroup::MotorGroup(const MotorGroup& copy)
{
    for (pros::Motor motor : copy.motors)
        motors.push_back(motor);
}

double MotorGroup::bindPower(double power)
{
    return std::min(127.0, std::abs(power)) * sign<double>(power);
}

double MotorGroup::bindVoltage(double power)
{
    return std::min(12000.0, std::abs(power)) * sign<double>(power);
}

double MotorGroup::bindVelocity(double velocity)
{
    if (!motors.empty())
    {
        switch(motors.front().get_gearing())
        {
        case pros::E_MOTOR_GEAR_100:
            velocity = std::min(100.0, std::abs(velocity)) * sign<double>(velocity);
            break;
        case pros::E_MOTOR_GEAR_200:
            velocity = std::min(200.0, std::abs(velocity)) * sign<double>(velocity);
            break;
        case pros::E_MOTOR_GEAR_600:
            velocity = std::min(600.0, std::abs(velocity)) * sign<double>(velocity);
            break;
        case pros::E_MOTOR_GEARSET_INVALID:
            velocity = 0.0;
            break;
        }
    }
    else
        velocity = 0.0;
    return velocity;
}

void MotorGroup::add_motor(pros::Motor& motor)
{
    mutex.take();
    motors.push_back(motor);
    mutex.give();
}

int MotorGroup::size()
{
    mutex.take();
    int size = motors.size();
    mutex.give();
    return size;
}

void MotorGroup::move(double power)
{
    mutex.take();
    power = bindPower(power);
    for (pros::Motor motor : motors)
        motor.move(power);
    mutex.give();
}

void MotorGroup::move_absolute(double position, double velocity)
{
    mutex.take();
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.move_absolute(position, velocity);
    mutex.give();
}

void MotorGroup::move_relative(double position, double velocity)
{
    mutex.take();
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.move_relative(position, velocity);
    mutex.give();
}

void MotorGroup::move_velocity(double velocity)
{
    mutex.take();
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.move_velocity(velocity);
    mutex.give();
}

void MotorGroup::move_voltage(double voltage)
{
    mutex.take();
    voltage = bindVoltage(voltage);
    for (pros::Motor motor : motors)
        motor.move_voltage(voltage);
    mutex.give();
}

void MotorGroup::brake()
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.brake();
    mutex.give();
}

void MotorGroup::modify_profiled_velocity(double velocity)
{
    mutex.take();
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.modify_profiled_velocity(velocity);
    mutex.give();
}

double MotorGroup::get_target_position()
{
    double position = 0.0;
    if (!motors.empty())
    {
        mutex.take();
        position = motors.front().get_target_position();
        mutex.give();
    }
    return position;
}

int MotorGroup::get_target_velocity()
{
    int velocity = 0;
    if (!motors.empty())
    {
        mutex.take();
        velocity = motors.front().get_target_velocity();
        mutex.give();
    }
    return velocity;
}

double MotorGroup::get_actual_velocity()
{
    double velocity = 0.0;
    mutex.take();
    for (pros::Motor motor : motors)
        velocity += motor.get_actual_velocity();
    if (!motors.empty())
        velocity /= motors.size();
    mutex.give();
    return velocity;
}

int MotorGroup::get_current_draw()
{
    int current = 0;
    mutex.take();
    for (pros::Motor motor : motors)
        current += motor.get_current_draw();
    if (!motors.empty())
        current /= motors.size();
    mutex.give();
    return current;
}

int MotorGroup::get_direction()
{
    int direction = 1;
    if (!motors.empty())
    {
        mutex.take();
        direction = motors.front().get_direction();
        mutex.give();
    }
    return direction;
}

int MotorGroup::get_efficiency()
{
    int efficiency = 0;
    mutex.take();
    for (pros::Motor motor : motors)
        efficiency += motor.get_efficiency();
    if (!motors.empty())
        efficiency /= motors.size();
    mutex.give();
    return efficiency;
}

int MotorGroup::get_faults()
{
    int faults = 0;
    mutex.take();
    for (pros::Motor motor : motors)
        faults &= motor.get_faults();
    mutex.give();
    return faults;
}

int MotorGroup::get_flags()
{
    int flags = 0;
    mutex.take();
    for (pros::Motor motor : motors)
        flags &= motor.get_flags();
    mutex.give();
    return flags;
}

double MotorGroup::get_position()
{
    double position = 0.0;
    mutex.take();
    for (pros::Motor motor : motors)
        position += motor.get_position();
    if (!motors.empty())
        position /= motors.size();
    mutex.give();
    return position;
}

double MotorGroup::get_power()
{
    double power = 0.0;
    mutex.take();
    for (pros::Motor motor : motors)
        power += motor.get_power();
    if (!motors.empty())
        power /= motors.size();
    mutex.give();
    return power;
}

int MotorGroup::get_raw_position(uint32_t* timestamp)
{
    int position = 0;
    mutex.take();
    for (pros::Motor motor : motors)
        position += motor.get_raw_position(timestamp);
    if (!motors.empty())
        position /= motors.size();
    mutex.give();
    return position;
}

double MotorGroup::get_temperature()
{
    double temperature = 0.0;
    mutex.take();
    for (pros::Motor motor : motors)
        temperature += motor.get_temperature();
    if (!motors.empty())
        temperature /= motors.size();
    mutex.give();
    return temperature;
}

double MotorGroup::get_torque()
{
    double torque = 0.0;
    mutex.take();
    for (pros::Motor motor : motors)
        torque += motor.get_torque();
    if (!motors.empty())
        torque /= motors.size();
    mutex.give();
    return torque;
}

int MotorGroup::get_voltage()
{
    int voltage = 0;
    mutex.take();
    for (pros::Motor motor : motors)
        voltage += motor.get_voltage();
    if (!motors.empty())
        voltage /= motors.size();
    mutex.give();
    return voltage;
}

int MotorGroup::get_zero_position_flag()
{
    int flag = 0;
    if (!motors.empty())
    {
        mutex.take();
        flag = motors.front().get_zero_position_flag();
        mutex.give();
    }
    return flag;
}

bool MotorGroup::is_stopped()
{
    bool stopped = false;
    if (!motors.empty())
    {
        mutex.take();
        stopped = motors.front().is_stopped();
        mutex.give();
    }
    return stopped;
}

bool MotorGroup::is_over_current()
{
    bool over = false;
    if (!motors.empty())
    {
        mutex.take();
        over = motors.front().is_over_current();
        mutex.give();
    }
    return over;
}

bool MotorGroup::is_over_temp()
{
    bool over = false;
    if (!motors.empty())
    {
        mutex.take();
        over = motors.front().is_over_temp();
        mutex.give();
    }
    return over;
}

pros::motor_brake_mode_e_t MotorGroup::get_brake_mode()
{
    pros::motor_brake_mode_e_t brake_mode =pros::E_MOTOR_BRAKE_INVALID;
    if (!motors.empty())
    {
        mutex.take();
        brake_mode = motors.front().get_brake_mode();
        mutex.give();
    }
    return brake_mode;
}

int MotorGroup::get_current_limit()
{
    int limit = 0;
    if (!motors.empty())
    {
        mutex.take();
        limit = motors.front().get_current_limit();
        mutex.give();
    }
    return limit;
}

pros::motor_encoder_units_e_t MotorGroup::get_encoder_units()
{
    pros::motor_encoder_units_e_t encoder_units = pros::E_MOTOR_ENCODER_INVALID;
    if (!motors.empty())
    {
        mutex.take();
        encoder_units = motors.front().get_encoder_units();
        mutex.give();
    }
    return encoder_units;
}

pros::motor_gearset_e_t MotorGroup::get_gearing()
{
    pros::motor_gearset_e_t gearing = pros::E_MOTOR_GEARSET_INVALID;
    if (!motors.empty())
    {
        mutex.take();
        gearing = motors.front().get_gearing();
        mutex.give();
    }
    return gearing;
}

std::vector<int> MotorGroup::get_ports()
{
    std::vector<int> ports;
    mutex.take();
    for (pros::Motor motor : motors)
        ports.push_back(motor.get_port());
    mutex.give();
    return ports;
}

int MotorGroup::get_voltage_limit()
{
    int limit = 0;
    if (!motors.empty())
    {
        mutex.take();
        limit = motors.front().get_voltage_limit();
        mutex.give();
    }
    return limit;
}

void MotorGroup::set_brake_mode(pros::motor_brake_mode_e_t mode)
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.set_brake_mode(mode);
    mutex.give();
}

void MotorGroup::set_current_limit(int limit)
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.set_current_limit(limit);
    mutex.give();
}

void MotorGroup::set_encoder_units(pros::motor_encoder_units_e_t units)
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.set_encoder_units(units);
    mutex.give();
}

void MotorGroup::set_gearing(pros::motor_gearset_e_t gearset)
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.set_gearing(gearset);
    mutex.give();
}

void MotorGroup::set_voltage_limit(int limit)
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.set_voltage_limit(limit);
    mutex.give();
}

void MotorGroup::set_zero_position(double position)
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.set_zero_position(position);
    mutex.give();
}

void MotorGroup::tare_position()
{
    mutex.take();
    for (pros::Motor motor : motors)
        motor.tare_position();
    mutex.give();
}

MotorGroup& MotorGroup::operator=(const MotorGroup& rhs)
{
    mutex.take();
    motors.clear();
    for (pros::Motor motor : rhs.motors)
        motors.push_back(motor);
    mutex.give();
    return *this;
}