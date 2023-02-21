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
     * The file name of the background image
     */
    static constexpr char BACKGROUND_FILE[50] = "S:/usd/images/background_menu.bin";

    /**
     * The current menu type
     */
    MenuTypes::Submenu currentMenu;

    /**
     * The current menu screen
     */
    MenuScreen* currentScreen;

    /**
     * The background image
     */
    lv_obj_t* background;

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