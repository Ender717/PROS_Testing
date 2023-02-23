// Inclusion guard
#ifndef PISTON_GROUP_H
#define PISTON_GROUP_H

// Included libraries
#include <vector>

// Included headers
#include "main.h"

/**
 * This class manages a group of pistons
 * @author Nathan Sandvig
 */
class PistonGroup
{
private:
    /**
     * The pistons in the group
     */
    std::vector<pros::ADIDigitalOut> pistons;

    /**
     * Whether the pistons are toggled
     */
    bool toggled;

public:
    /**
     * Default constructor
     */
    PistonGroup();

    /**
     * Copy constructor
     * @param copy The PistonGroup being copied
     */
    PistonGroup(const PistonGroup& copy);

    /**
     * Adds a piston to the group
     * @param piston The piston
     */
    void add_piston(pros::ADIDigitalOut piston);

    /**
     * Gets the size of the piston group
     * @return The size of the group
     */
    int size();

    /**
     * Toggles the pistons
     */
    void toggle();

    /**
     * Checks if the pistons are toggled
     * @return True if the pistons are toggled, false if not
     */
    bool are_toggled();

    /**
     * Assignment operator overload
     * @param rhs The PistonGroup on the right hand side of the operator
     * @return This PistonGroup with the assigned values
     */
    PistonGroup& operator=(const PistonGroup& rhs);
};

#endif