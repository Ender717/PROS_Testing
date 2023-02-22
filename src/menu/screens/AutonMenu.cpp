// Included headers
#include "menu/screens/AutonMenu.h"

AutonMenu::AutonMenu() : OptionScreen(HEADER_FILE, MenuTypes::AUTON_STR, MenuTypes::AUTON_COUNT, BUTTONS_PER_LINE, static_cast<int>(MenuData::getAuton()))
{
    lv_btnm_set_action(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), buttonEvent);
}

lv_res_t AutonMenu::buttonEvent(lv_obj_t* buttonmatrix, const char* text)
{
    for (int i = 0; i < MenuTypes::AUTON_COUNT; i++)
        if (text == MenuTypes::AUTON_STR[i])
            MenuData::setAuton(static_cast<MenuTypes::Auton>(i));
    MenuData::writeData();

    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);
    return LV_RES_OK;
}

void AutonMenu::pressButton()
{
    buttonEvent(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), MenuTypes::AUTON_STR[current_index]);
}

void AutonMenu::update(pros::Controller& controller)
{
    OptionScreen::update(controller);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}