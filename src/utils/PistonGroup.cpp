// Included headers
#include "utils/PistonGroup.h"
#include "pros/adi.hpp"

PistonGroup::PistonGroup()
{

}

PistonGroup::PistonGroup(const PistonGroup& copy)
{
    for (pros::ADIDigitalOut piston : copy.pistons)
        pistons.push_back(piston);
}

void PistonGroup::add_piston(pros::ADIDigitalOut& piston)
{
    mutex.take();
    pistons.push_back(piston);
    mutex.give();
}

int PistonGroup::size()
{
    mutex.take();
    int size = pistons.size();
    mutex.give();
    return size;
}

void PistonGroup::toggle()
{
    mutex.take();
    toggled = !toggled;
    for (pros::ADIDigitalOut piston : pistons)
        piston.set_value(toggled);
    mutex.give();
}

bool PistonGroup::are_toggled()
{
    mutex.take();
    bool result = toggled;
    mutex.give();
    return result;
}

PistonGroup& PistonGroup::operator=(const PistonGroup& rhs)
{
    mutex.take();
    pistons.clear();
    for (pros::ADIDigitalOut piston : rhs.pistons)
        pistons.push_back(piston);
    mutex.give();
    return *this;
}