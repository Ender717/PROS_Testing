// Inclusion guard
#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

// Included headers
#include "main.h"
#include "MenuTypes.h"
#include "MenuData.h"

/**
 * This class manages a screen in the menu
 * @author Nathan Sandvig
 */
class MenuScreen
{
public:
    /**
     * Virtual destructor
     */
    virtual ~MenuScreen() = default;

    /**
     * Opens the menu screen
     */
    virtual void open() = 0;

    /**
     * Closes the menu screen
     */
    virtual void close() = 0;

    /**
     * Updates the menu screen
     * @param controller The input controller
     */
    virtual void update(pros::Controller& controller) = 0;
};

#endif