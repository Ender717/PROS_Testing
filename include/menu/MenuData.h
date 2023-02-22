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
     * The controlled instance
     */
    static MenuData* instance;

    /**
     * The alliance setting
     */
    MenuTypes::Alliance alliance;

    /**
     * The auton setting
     */
    MenuTypes::Auton auton;

    /**
     * The config setting
     */
    MenuTypes::Config config;

    /**
     * The profile setting
     */
    MenuTypes::Profile profile;

    /**
     * The menu setting
     */
    MenuTypes::Submenu submenu;

    /**
     * Private constructor to prevent uncontrolled construction
     */
    MenuData();

public:
    /**
     * Remove the copy constructor
     */
    MenuData(const MenuData& copy) = delete;

    /**
     * Remove the assignment operator
     */
    MenuData& operator=(const MenuData& rhs) = delete;

    /**
     * Gets the controlled instance of menu data
     */
    static MenuData* getInstance();

    /**
     * Sets the alliance setting
     * @param _alliance The alliance setting
     */
    void setAlliance(MenuTypes::Alliance _alliance);

    /**
     * Gets the alliance setting
     * @return The alliance setting
     */
    MenuTypes::Alliance getAlliance();

    /**
     * Sets the auton setting
     * @param _auton The auton setting
     */
    void setAuton(MenuTypes::Auton _auton);

    /**
     * Gets the auton setting
     * @return The auton setting
     */
    MenuTypes::Auton getAuton();

    /**
     * Sets the config setting
     * @param _config The config setting
     */
    void setConfig(MenuTypes::Config _config);

    /**
     * Gets the config setting
     * @return The config setting
     */
    MenuTypes::Config getConfig();

    /**
     * Sets the profile setting
     * @param _profile The profile setting
     */
    void setProfile(MenuTypes::Profile _profile);

    /**
     * Gets the profile setting
     * @return The profile setting
     */
    MenuTypes::Profile getProfile();

    /**
     * Sets the submenu setting
     * @param _submenu The submenu setting
     */
    void setSubmenu(MenuTypes::Submenu _submenu);

    /**
     * Gets the submenu setting
     * @return The submenu setting
     */
    MenuTypes::Submenu getSubmenu();

    /**
     * Reads the menu data from a file
     */
    void readData();

    /**
     * Writes the menu data to a file
     */
    void writeData();
};

#endif