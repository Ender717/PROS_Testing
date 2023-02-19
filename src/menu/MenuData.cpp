// Included headers
#include "menu/MenuData.h"

MenuTypes::Alliance MenuData::alliance = MenuTypes::Alliance::BLUE;
MenuTypes::Auton MenuData::auton = MenuTypes::Auton::BLUE_LEFT;
MenuTypes::Config MenuData::config = MenuTypes::Config::BLUE;
MenuTypes::Profile MenuData::profile = MenuTypes::Profile::HENRY;
MenuTypes::Submenu MenuData::submenu = MenuTypes::Submenu::CLOSED;

void MenuData::setAlliance(MenuTypes::Alliance alliance)
{
    MenuData::alliance = alliance;
}

MenuTypes::Alliance MenuData::getAlliance()
{
    return alliance;
}

void MenuData::setAuton(MenuTypes::Auton auton)
{
    MenuData::auton = auton;
}

MenuTypes::Auton MenuData::getAuton()
{
    return auton;
}

void MenuData::setConfig(MenuTypes::Config config)
{
    MenuData::config = config;
}

MenuTypes::Config MenuData::getConfig()
{
    return config;
}

void MenuData::setProfile(MenuTypes::Profile profile)
{
    MenuData::profile = profile;
}

MenuTypes::Profile MenuData::getProfile()
{
    return profile;
}

void MenuData::setSubmenu(MenuTypes::Submenu submenu)
{
    MenuData::submenu = submenu;
}

MenuTypes::Submenu MenuData::getSubmenu()
{
    return submenu;
}

void MenuData::readData()
{
    // Open the input file
    std::ifstream input(MENU_FILE);
    if (input.fail())
    {
        input.close();
        return;
    }

    // Read the alliance data
    char allianceData[BUFFER_SIZE];
    input >> allianceData;
    for (int i = 0; i < MenuTypes::ALLIANCE_COUNT; i++)
        if (allianceData == MenuTypes::ALLIANCE_STR[i])
            alliance = static_cast<MenuTypes::Alliance>(i);

    // Read the auton data
    char autonData[BUFFER_SIZE];
    input >> autonData;
    for (int i = 0; i < MenuTypes::AUTON_COUNT; i++)
        if (autonData == MenuTypes::AUTON_STR[i])
            auton = static_cast<MenuTypes::Auton>(i);

    // Read the config data
    char configData[BUFFER_SIZE];
    input >> configData;
    for (int i = 0; i < MenuTypes::CONFIG_COUNT; i++)
        if (configData == MenuTypes::CONFIG_STR[i])
            config = static_cast<MenuTypes::Config>(i);

    // Read the profile data
    char profileData[BUFFER_SIZE];
    input >> profileData;
    for (int i = 0; i < MenuTypes::PROFILE_COUNT; i++)
        if (profileData == MenuTypes::PROFILE_STR[i])
            profile = static_cast<MenuTypes::Profile>(i);

    // Close the input file
    input.close();
}

void MenuData::writeData()
{
    // Open the output file
    std::ofstream output(MENU_FILE);
    if (output.fail())
    {
        output.close();
        return;
    }

    // Output the current menu settings
    output << MenuTypes::ALLIANCE_STR[static_cast<int>(alliance)] << std::endl;
    output << MenuTypes::AUTON_STR[static_cast<int>(auton)] << std::endl;
    output << MenuTypes::CONFIG_STR[static_cast<int>(config)] << std::endl;
    output << MenuTypes::PROFILE_STR[static_cast<int>(profile)] << std::endl;

    // Close the output file
    output.close();
}