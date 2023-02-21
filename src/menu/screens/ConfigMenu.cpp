// Included headers
#include "menu/screens/ConfigMenu.h"

ConfigMenu::ConfigMenu() : OptionScreen(HEADER_FILE, MenuTypes::CONFIG_STR, MenuTypes::CONFIG_COUNT, BUTTONS_PER_LINE, static_cast<int>(MenuData::getConfig()))
{
    lv_btnm_set_action(button_matrix, buttonEvent);
}

lv_res_t ConfigMenu::buttonEvent(lv_obj_t* buttonmatrix, const char* text)
{
    for (int i = 0; i < MenuTypes::CONFIG_COUNT; i++)
        if (text == MenuTypes::CONFIG_STR[i])
            MenuData::setConfig(static_cast<MenuTypes::Config>(i));
    MenuData::writeData();

    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);
    return LV_RES_OK;
}

void ConfigMenu::pressButton()
{
    buttonEvent(button_matrix, MenuTypes::CONFIG_STR[current_index]);
}

void ConfigMenu::update(pros::Controller& controller)
{
    OptionScreen::update(controller);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}