// Included headers
#include "menu/MenuData.h"

void MenuData::setAlliance(MenuTypes::Alliance _alliance)
{
    mutex.take();
    alliance = _alliance;
    mutex.give();
}

MenuTypes::Alliance MenuData::getAlliance()
{
    mutex.take();
    MenuTypes::Alliance result = alliance;
    mutex.give();
    return result;
}

void MenuData::setAuton(MenuTypes::Auton _auton)
{
    mutex.take();
    auton = _auton;
    mutex.give();
}

MenuTypes::Auton MenuData::getAuton()
{
    mutex.take();
    MenuTypes::Auton result = auton;
    mutex.give();
    return result;
}

void MenuData::setConfig(MenuTypes::Config _config)
{
    mutex.take();
    config = _config;
    mutex.give();
}

MenuTypes::Config MenuData::getConfig()
{
    mutex.take();
    MenuTypes::Config result = config;
    mutex.give();
    return result;
}

void MenuData::setProfile(MenuTypes::Profile _profile)
{
    mutex.take();
    profile = _profile;
    mutex.give();
}

MenuTypes::Profile MenuData::getProfile()
{
    mutex.take();
    MenuTypes::Profile result = profile;
    mutex.give();
    return result;
}

void MenuData::setSubmenu(MenuTypes::Submenu _submenu)
{
    mutex.take();
    submenu = _submenu;
    mutex.give();
}

MenuTypes::Submenu MenuData::getSubmenu()
{
    mutex.take();
    MenuTypes::Submenu result = submenu;
    mutex.give();
    return result;
}

void MenuData::readData()
{
    mutex.take();

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

    mutex.give();
}

void MenuData::writeData()
{
    mutex.take();

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

    mutex.give();
}