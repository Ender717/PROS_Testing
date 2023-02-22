// Included headers
#include "menu/screens/ConfigMenu.h"

ConfigMenu::ConfigMenu() : OptionScreen(HEADER_FILE, MenuTypes::CONFIG_STR, MenuTypes::CONFIG_COUNT, BUTTONS_PER_LINE, 0)
{
    lv_btnm_set_action(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), buttonEvent);
}

lv_res_t ConfigMenu::buttonEvent(lv_obj_t* buttonmatrix, const char* text)
{
    MenuData* menuData = MenuData::getInstance();
    for (int i = 0; i < MenuTypes::CONFIG_COUNT; i++)
        if (text == MenuTypes::CONFIG_STR[i])
            menuData->setConfig(static_cast<MenuTypes::Config>(i));
    menuData->writeData();

    menuData->setSubmenu(MenuTypes::Submenu::MAIN);
    return LV_RES_OK;
}

void ConfigMenu::pressButton()
{
    buttonEvent(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), MenuTypes::CONFIG_STR[current_index]);
}

void ConfigMenu::update(pros::Controller& controller)
{
    OptionScreen::update(controller);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}