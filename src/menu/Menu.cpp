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
    currentMenu = MenuTypes::Submenu::MAIN;
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::MAIN);
    currentScreen = new MainMenu;
    running = true;
}

void Menu::close()
{
    currentMenu = MenuTypes::Submenu::CLOSED;
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::CLOSED);
    if (currentScreen != nullptr)
    {
        delete currentScreen;
        currentScreen = nullptr;
    }
    running = false;
}

void Menu::update(pros::Controller& controller)
{
    MenuData* menuData = MenuData::getInstance();
    // Check for a submenu update
    if (currentMenu == menuData->getSubmenu())
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
    currentMenu = menuData->getSubmenu();

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
}

bool Menu::isRunning()
{
    return running;
}