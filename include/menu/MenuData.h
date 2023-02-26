// Inclusion guard
#ifndef MENU_DATA_H
#define MENU_DATA_H

// Included libraries
#include <fstream>

// Included headers
#include "main.h"
#include "MenuTypes.h"

/**
 * This class manages the selected menu information
 * @author Nathan Sandvig
 */
class MenuData
{
private:
    /**
     * The name of the file used for menu data storage
     */
    static constexpr char MENU_FILE[20] = "/usd/MenuData.txt";

    /**
     * The buffer size of input/output character arrays
     */
    static constexpr int BUFFER_SIZE = 20;

    /**
     * The mutex that keeps the menu data threadsafe
     */
    static pros::Mutex mutex;

    /**
     * The alliance setting
     */
    static MenuTypes::Alliance alliance;

    /**
     * The auton setting
     */
    static MenuTypes::Auton auton;

    /**
     * The config setting
     */
    static MenuTypes::Config config;

    /**
     * The profile setting
     */
    static MenuTypes::Profile profile;

    /**
     * The menu setting
     */
    static MenuTypes::Submenu submenu;

public:
    /**
     * Sets the alliance in the menu data
     * @param _alliance The new alliance
     */
    static void setAlliance(MenuTypes::Alliance _alliance);

    /**
     * Gets the alliance setting from the menu data
     * @return The alliance setting
     */
    static MenuTypes::Alliance getAlliance();

    /**
     * Sets the auton in the menu data
     * @param _auton The new auton
     */
    static void setAuton(MenuTypes::Auton _auton);

    /**
     * Gets the auton setting from the menu data
     * @return The auton setting
     */
    static MenuTypes::Auton getAuton();

    /**
     * Sets the config in the menu data
     * @param _config The new config
     */
    static void setConfig(MenuTypes::Config _config);

    /**
     * Gets the config setting from the menu data
     * @return The config setting
     */
    static MenuTypes::Config getConfig();

    /**
     * Sets the profile in the menu data
     * @param _profile The profile setting
     */
    static void setProfile(MenuTypes::Profile _profile);

    /**
     * Gets the profile setting from the menu data
     * @return The profile setting
     */
    static MenuTypes::Profile getProfile();

    /**
     * Sets the submenu in the menu data
     * @param _submenu The submenu setting
     */
    static void setSubmenu(MenuTypes::Submenu _submenu);

    /**
     * Gets the submenu setting from the menu data
     * @return The submenu setting
     */
    static MenuTypes::Submenu getSubmenu();

    /**
     * Reads the menu data from a file
     */
    static void readData();

    /**
     * Writes the menu data to a file
     */
    static void writeData();
};

#endif