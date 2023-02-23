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
    return velocity;
}

void MotorGroup::add_motor(pros::Motor motor)
{
    motors.push_back(motor);
}

int MotorGroup::size()
{
    return motors.size();
}

void MotorGroup::move(double power)
{
    power = bindPower(power);
    for (pros::Motor motor : motors)
        motor.move(power);
}

void MotorGroup::move_absolute(double position, double velocity)
{
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.move_absolute(position, velocity);
}

void MotorGroup::move_relative(double position, double velocity)
{
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.move_relative(position, velocity);
}

void MotorGroup::move_velocity(double velocity)
{
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.move_velocity(velocity);
}

void MotorGroup::move_voltage(double voltage)
{
    voltage = bindVoltage(voltage);
    for (pros::Motor motor : motors)
        motor.move_voltage(voltage);
}

void MotorGroup::brake()
{
    for (pros::Motor motor : motors)
        motor.brake();
}

void MotorGroup::modify_profiled_velocity(double velocity)
{
    velocity = bindVelocity(velocity);
    for (pros::Motor motor : motors)
        motor.modify_profiled_velocity(velocity);
}

double MotorGroup::get_target_position()
{
    if (!motors.empty())
        return motors.front().get_target_position();
    else
        return 0.0;
}

double MotorGroup::get_target_velocity()
{
    if (!motors.empty())
        return motors.front().get_target_velocity();
    else
        return 0.0;
}

double MotorGroup::get_actual_velocity()
{
    double velocity = 0.0;
    for (pros::Motor motor : motors)
        velocity += motor.get_actual_velocity();
    if (!motors.empty())
        velocity /= motors.size();
    return velocity;
}

int MotorGroup::get_current_draw()
{
    int current = 0;
    for (pros::Motor motor : motors)
        current += motor.get_current_draw();
    if (!motors.empty())
        current /= motors.size();
    return current;
}

int MotorGroup::get_direction()
{
    if (!motors.empty())
        return motors.front().get_direction();
    else
        return 1;
}

int MotorGroup::get_efficiency()
{
    int efficiency = 0;
    for (pros::Motor motor : motors)
        efficiency += motor.get_efficiency();
    if (!motors.empty())
        efficiency /= motors.size();
    return efficiency;
}

int MotorGroup::get_faults()
{
    int faults = 0;
    for (pros::Motor motor : motors)
        faults &= motor.get_faults();
    return faults;
}

int MotorGroup::get_flags()
{
    int flags = 0;
    for (pros::Motor motor : motors)
        flags &= motor.get_flags();
    return flags;
}

double MotorGroup::get_position()
{
    double position = 0.0;
    for (pros::Motor motor : motors)
        position += motor.get_position();
    if (!motors.empty())
        position /= motors.size();
    return position;
}

double MotorGroup::get_power()
{
    double power = 0.0;
    for (pros::Motor motor : motors)
        power += motor.get_power();
    if (!motors.empty())
        power /= motors.size();
    return power;
}

int MotorGroup::get_raw_position(unsigned int* timestamp)
{
    int position = 0;
    for (pros::Motor motor : motors)
        position += motor.get_raw_position(timestamp);
    if (!motors.empty())
        position /= motors.size();
    return position;
}

double MotorGroup::get_temperature()
{
    double temperature = 0.0;
    for (pros::Motor motor : motors)
        temperature += motor.get_temperature();
    if (!motors.empty())
        temperature /= motors.size();
    return temperature;
}

double MotorGroup::get_torque()
{
    double torque = 0.0;
    for (pros::Motor motor : motors)
        torque += motor.get_torque();
    if (!motors.empty())
        torque /= motors.size();
    return torque;
}

int MotorGroup::get_voltage()
{
    int voltage = 0;
    for (pros::Motor motor : motors)
        voltage += motor.get_voltage();
    if (!motors.empty())
        voltage /= motors.size();
    return voltage;
}

int MotorGroup::get_zero_position_flag()
{
    if (!motors.empty())
        return motors.front().get_zero_position_flag();
    else
        return 0;
}

bool MotorGroup::is_stopped()
{
    if (!motors.empty())
        return motors.front().is_stopped();
    else
        return false;
}

bool MotorGroup::is_over_current()
{
    if (!motors.empty())
        return motors.front().is_over_current();
    else
        return false;
}

bool MotorGroup::is_over_temp()
{
    if (!motors.empty())
        return motors.front().is_over_temp();
    else
        return false;
}

pros::motor_brake_mode_e_t MotorGroup::get_brake_mode()
{
    if (!motors.empty())
        return motors.front().get_brake_mode();
    else
        return pros::E_MOTOR_BRAKE_INVALID;
}

int MotorGroup::get_current_limit()
{
    if (!motors.empty())
        return motors.front().get_current_limit();
    else
        return 0;
}

pros::motor_encoder_units_e_t MotorGroup::get_encoder_units()
{
    if (!motors.empty())
        return motors.front().get_encoder_units();
    else
        return pros::E_MOTOR_ENCODER_INVALID;
}

pros::motor_gearset_e_t MotorGroup::get_gearing()
{
    if (!motors.empty())
        return motors.front().get_gearing();
    else
        return pros::E_MOTOR_GEARSET_INVALID;
}

std::vector<int> MotorGroup::get_ports()
{
    std::vector<int> ports;
    for (pros::Motor motor : motors)
        ports.push_back(motor.get_port());
    return ports;
}

int MotorGroup::get_voltage_limit()
{
    if (!motors.empty())
        return motors.front().get_voltage_limit();
    else
        return 0;
}

void MotorGroup::set_brake_mode(pros::motor_brake_mode_e_t mode)
{
    for (pros::Motor motor : motors)
        motor.set_brake_mode(mode);
}

void MotorGroup::set_current_limit(int limit)
{
    for (pros::Motor motor : motors)
        motor.set_current_limit(limit);
}

void MotorGroup::set_encoder_units(pros::motor_encoder_units_e_t units)
{
    for (pros::Motor motor : motors)
        motor.set_encoder_units(units);
}

void MotorGroup::set_gearing(pros::motor_gearset_e_t gearset)
{
    for (pros::Motor motor : motors)
        motor.set_gearing(gearset);
}

void MotorGroup::set_voltage_limit(int limit)
{
    for (pros::Motor motor : motors)
        motor.set_voltage_limit(limit);
}

void MotorGroup::set_zero_position(double position)
{
    for (pros::Motor motor : motors)
        motor.set_zero_position(position);
}

void MotorGroup::tare_position()
{
    for (pros::Motor motor : motors)
        motor.tare_position();
}