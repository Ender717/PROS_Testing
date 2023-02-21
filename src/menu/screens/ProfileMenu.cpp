// Included headers
#include "menu/screens/ProfileMenu.h"

ProfileMenu::ProfileMenu() : OptionScreen(HEADER_FILE, MenuTypes::PROFILE_STR, MenuTypes::PROFILE_COUNT, BUTTONS_PER_LINE, static_cast<int>(MenuData::getProfile()))
{
    lv_btnm_set_action(button_matrix, buttonEvent);
}

lv_res_t ProfileMenu::buttonEvent(lv_obj_t* buttonmatrix, const char* text)
{
    for (int i = 0; i < MenuTypes::PROFILE_COUNT; i++)
        if (text == MenuTypes::PROFILE_STR[i])
            MenuData::setProfile(static_cast<MenuTypes::Profile>(i));
    MenuData::writeData();

    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);
    return LV_RES_OK;
}

void ProfileMenu::pressButton()
{
    buttonEvent(button_matrix, MenuTypes::PROFILE_STR[current_index]);
}

void ProfileMenu::update(pros::Controller& controller)
{
    OptionScreen::update(controller);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}