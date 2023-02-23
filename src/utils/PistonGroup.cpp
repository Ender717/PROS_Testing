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

void PistonGroup::add_piston(pros::ADIDigitalOut piston)
{
    pistons.push_back(piston);
}

int PistonGroup::size()
{
    return pistons.size();
}

void PistonGroup::toggle()
{
    toggled = !toggled;
    for (pros::ADIDigitalOut piston : pistons)
        piston.set_value(toggled);
}

bool PistonGroup::are_toggled()
{
    return toggled;
}

PistonGroup& PistonGroup::operator=(const PistonGroup& rhs)
{
    pistons.clear();
    for (pros::ADIDigitalOut piston : rhs.pistons)
        pistons.push_back(piston);
    return *this;
}