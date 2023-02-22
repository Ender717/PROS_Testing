// Inclusion guard
#ifndef MENU_TYPES_H
#define MENU_TYPES_H

/**
 * This namespace holds all types used by the menu system
 * @author Nathan Sandvig
 */
namespace MenuTypes
{
    /**
     * This enum holds the possible values for the alliance
     */
    enum class Alliance
    {
        BLUE,
        RED,
        SKILLS
    };
    static const char* ALLIANCE_STR[] = { "BLUE", "RED", "SKILLS" };
    static const int ALLIANCE_COUNT = 3;

    /**
     * This enum holds the possible values for the auton
     */
    enum class Auton
    {
        BLUE_LEFT,
        BLUE_RIGHT,
        ORANGE_LEFT,
        ORANGE_RIGHT,
        SKILLS_LEFT,
        SKILLS_RIGHT
    };
    static const char* AUTON_STR[] = { "BLUE_LEFT", "BLUE_RIGHT", "ORANGE_LEFT", "ORANGE_RIGHT", "SKILLS_LEFT", "SKILLS_RIGHT" };
    static const int AUTON_COUNT = 6;

    /**
     * This enum holds the possible values for the config
     */
    enum class Config
    {
        BLUE,
        ORANGE
    };
    static const char* CONFIG_STR[] = { "BLUE", "ORANGE" };
    static const int CONFIG_COUNT = 2;

    /**
     * This enum holds the possible values for the profile
     */
    enum class Profile
    {
        HENRY,
        JOHN,
        NATHAN
    };
    static const char* PROFILE_STR[] = { "HENRY", "JOHN", "NATHAN" };
    static const int PROFILE_COUNT = 3;

    /**
     * This enum holds the possible values for the submenu
     */
    enum class Submenu
    {
        MAIN,
        ALLIANCE,
        AUTON,
        CONFIG,
        PROFILE,
        CLOSED
    };
    static const char* SUBMENU_STR[] = { "MAIN", "ALLIANCE", "AUTON", "CONFIG", "PROFILE", "CLOSED" };
    static const int SUBMENU_COUNT = 6;
};

#endif