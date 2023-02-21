// Included headers
#include "menu/Menu.h"

Menu::Menu()
{
    currentMenu = MenuTypes::Submenu::CLOSED;
    currentScreen = nullptr;
    background = nullptr;
    running = false;
}

Menu::~Menu()
{
    if (background != nullptr)
    {
        lv_obj_del(background);
        background = nullptr;
    }
    if (currentScreen != nullptr)
    {
        delete currentScreen;
        currentScreen = nullptr;
    }
}

void Menu::open()
{
    currentMenu = MenuTypes::Submenu::MAIN;
    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);

    background = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(background, BACKGROUND_FILE);
    lv_obj_set_pos(background, 0, 0);

    currentScreen = new MainMenu;
    running = true;
}

void Menu::close()
{
    currentMenu = MenuTypes::Submenu::CLOSED;
    MenuData::setSubmenu(MenuTypes::Submenu::CLOSED);
    if (currentScreen != nullptr)
    {
        delete currentScreen;
        currentScreen = nullptr;
    }
    lv_obj_del(background);
    background = nullptr;
    running = false;
}

void Menu::update(pros::Controller& controller)
{
    // Open the next screen
    if (currentScreen == nullptr)
    {
        pros::delay(800);
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
}

bool Menu::isRunning()
{
    return running;
}