// Inclusion guard
#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

// Included headers
#include "main.h"
#include "menu/MenuTypes.h"
#include "menu/MenuData.h"

/**
 * This class manages a screen in the menu
 * @author Nathan Sandvig
 */
class MenuScreen
{
protected:
    /**
     * The mutex to make the menu screen threadsafe
     */
    pros::Mutex mutex;

public:
    /**
     * Virtual destructor
     */
    virtual ~MenuScreen() = default;

    /**
     * Updates the menu screen
     * @param controller The input controller
     */
    virtual void update(pros::Controller& controller) = 0;
};

#endif