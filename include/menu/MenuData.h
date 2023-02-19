// Inclusion guard
#ifndef MENU_DATA_H
#define MENU_DATA_H

// Included libraries
#include <fstream>

// Included headers
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
     * Sets the alliance setting
     * @param alliance The alliance setting
     */
    static void setAlliance(MenuTypes::Alliance alliance);

    /**
     * Gets the alliance setting
     * @return The alliance setting
     */
    static MenuTypes::Alliance getAlliance();

    /**
     * Sets the auton setting
     * @param auton The auton setting
     */
    static void setAuton(MenuTypes::Auton auton);

    /**
     * Gets the auton setting
     * @return The auton setting
     */
    static MenuTypes::Auton getAuton();

    /**
     * Sets the config setting
     * @param config The config setting
     */
    static void setConfig(MenuTypes::Config config);

    /**
     * Gets the config setting
     * @return The config setting
     */
    static MenuTypes::Config getConfig();

    /**
     * Sets the profile setting
     * @param profile The profile setting
     */
    static void setProfile(MenuTypes::Profile profile);

    /**
     * Gets the profile setting
     * @return The profile setting
     */
    static MenuTypes::Profile getProfile();

    /**
     * Sets the submenu setting
     * @param submenu The submenu setting
     */
    static void setSubmenu(MenuTypes::Submenu submenu);

    /**
     * Gets the submenu setting
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