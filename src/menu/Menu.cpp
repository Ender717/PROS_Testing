// Included headers
#include "menu/Menu.h"

Menu::Menu()
{
    currentMenu = MenuTypes::Submenu::CLOSED;
    currentScreen = nullptr;
    running = false;
}

Menu::~Menu()
{
    if (currentScreen != nullptr)
    {
        currentScreen->close();
        delete currentScreen;
        currentScreen = nullptr;
    }
}

void Menu::open()
{
    if (currentScreen != nullptr)
    {
        currentScreen->close();
        delete currentScreen;
        currentScreen = nullptr;
    }

    currentMenu = MenuTypes::Submenu::MAIN;
    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);
    currentScreen = new MainMenu;
    currentScreen->open();
    running = true;
}

void Menu::close()
{
    currentMenu = MenuTypes::Submenu::CLOSED;
    MenuData::setSubmenu(MenuTypes::Submenu::CLOSED);
    if (currentScreen != nullptr)
    {
        currentScreen->close();
        delete currentScreen;
        currentScreen = nullptr;
    }
    running = false;
}

void Menu::update(pros::Controller& controller)
{
    // Check for a submenu update
    if (currentMenu == MenuData::getSubmenu())
    {
        currentScreen->update(controller);
        return;
    }

    // Update the submenu
    currentMenu = MenuData::getSubmenu();

    // Close the previous screen
    if (currentScreen != nullptr)
    {
        currentScreen->close();
        delete currentScreen;
        currentScreen = nullptr;
    }

    // Open the next screen
    switch(currentMenu)
    {
        case MenuTypes::Submenu::ALLIANCE:
            currentScreen = new AllianceMenu;
            break;
        case MenuTypes::Submenu::AUTON:
            // Create auton menu screen
            break;
        case MenuTypes::Submenu::CONFIG:
            // Create config menu screen
            break;
        case MenuTypes::Submenu::MAIN:
            currentScreen = new MainMenu;
            break;
        case MenuTypes::Submenu::PROFILE:
            // Create profile menu screen
            break;
        case MenuTypes::Submenu::CLOSED:
            running = false;
            break;
    }
    if (currentScreen != nullptr)
        currentScreen->open();
}

bool Menu::isRunning()
{
    return running;
}