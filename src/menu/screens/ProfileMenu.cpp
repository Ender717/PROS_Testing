// Included headers
#include "menu/screens/ProfileMenu.h"

ProfileMenu::ProfileMenu() : OptionScreen(HEADER_FILE, MenuTypes::PROFILE_STR, MenuTypes::PROFILE_COUNT, BUTTONS_PER_LINE, 0)
{
    lv_btnm_set_action(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), buttonEvent);
}

lv_res_t ProfileMenu::buttonEvent(lv_obj_t* buttonmatrix, const char* text)
{
    MenuData* menuData = MenuData::getInstance();
    for (int i = 0; i < MenuTypes::PROFILE_COUNT; i++)
        if (text == MenuTypes::PROFILE_STR[i])
            menuData->setProfile(static_cast<MenuTypes::Profile>(i));
    menuData->writeData();

    menuData->setSubmenu(MenuTypes::Submenu::MAIN);
    return LV_RES_OK;
}

void ProfileMenu::pressButton()
{
    buttonEvent(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), MenuTypes::PROFILE_STR[current_index]);
}

void ProfileMenu::update(pros::Controller& controller)
{
    OptionScreen::update(controller);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}