// Inclusion guard
#ifndef MENU_H
#define MENU_H

// Included headers
#include "MenuTypes.h"
#include "MenuData.h"
#include "screens/Screens.h"

/**
 * This class manages the menu system
 * @author Nathan Sandvig
 */
class Menu
{
private:
    /**
     * The current menu type
     */
    MenuTypes::Submenu currentMenu;

    /**
     * The current menu screen
     */
    MenuScreen* currentScreen;

    /**
     * Whether the menu is running or not
     */
    bool running;

public:
    /**
     * Default constructor
     */
    Menu();

    /**
     * Destructor
     */
    ~Menu();

    /**
     * Opens the menu
     */
    void open();

    /**
     * Closes the menu
     */
    void close();

    /**
     * Updates the menu
     */
    void update(pros::Controller& controller);

    /**
     * Checks if the menu is still running
     * @return True if the menu is running, false if not
     */
    bool isRunning();
};

#endif