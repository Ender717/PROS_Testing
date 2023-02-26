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
        delete currentScreen;
        currentScreen = nullptr;
    }
}

void Menu::open()
{
    mutex.take();
    currentMenu = MenuTypes::Submenu::MAIN;
    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);
    currentScreen = new MainMenu;
    running = true;
    mutex.give();
}

void Menu::close()
{
    mutex.take();
    currentMenu = MenuTypes::Submenu::CLOSED;
    MenuData::setSubmenu(MenuTypes::Submenu::CLOSED);
    if (currentScreen != nullptr)
    {
        delete currentScreen;
        currentScreen = nullptr;
    }
    running = false;
    mutex.give();
}

void Menu::update(pros::Controller& controller)
{
    mutex.take();

    // Check for a submenu update
    if (currentMenu == MenuData::getSubmenu())
    {
        if (currentScreen != nullptr)
            currentScreen->update(controller);
        return;
    }

    // Close the previous screen
    if (currentScreen != nullptr)
    {
        delete currentScreen;
        currentScreen = nullptr;
    }

    // Update the submenu
    currentMenu = MenuData::getSubmenu();

    // Open the next menu
    switch(currentMenu)
    {
        case MenuTypes::Submenu::ALLIANCE:
            currentScreen = new AllianceMenu;
            break;
        case MenuTypes::Submenu::AUTON:
            currentScreen = new AutonMenu;
            break;
        case MenuTypes::Submenu::CONFIG:
            currentScreen = new ConfigMenu;
            break;
        case MenuTypes::Submenu::MAIN:
            currentScreen = new MainMenu;
            break;
        case MenuTypes::Submenu::PROFILE:
            currentScreen = new ProfileMenu;
            break;
        case MenuTypes::Submenu::CLOSED:
            running = false;
            break;
    }

    mutex.give();
}

bool Menu::isRunning()
{
    mutex.take();
    bool result = running;
    mutex.give();
    return result;
}