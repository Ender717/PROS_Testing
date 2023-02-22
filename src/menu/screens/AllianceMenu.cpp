// Included headers
#include "menu/screens/AllianceMenu.h"

AllianceMenu::AllianceMenu() : OptionScreen(HEADER_FILE, MenuTypes::ALLIANCE_STR, MenuTypes::ALLIANCE_COUNT, BUTTONS_PER_LINE, static_cast<int>(MenuData::getAlliance()))
{
    lv_btnm_set_action(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), buttonEvent);
}

lv_res_t AllianceMenu::buttonEvent(lv_obj_t* buttonmatrix, const char* text)
{
    for (int i = 0; i < MenuTypes::ALLIANCE_COUNT; i++)
        if (text == MenuTypes::ALLIANCE_STR[i])
            MenuData::setAlliance(static_cast<MenuTypes::Alliance>(i));
    MenuData::writeData();

    MenuData::setSubmenu(MenuTypes::Submenu::MAIN);
    return LV_RES_OK;
}

void AllianceMenu::pressButton()
{
    buttonEvent(lv_obj_get_child(lv_scr_act(), lv_obj_get_child(lv_scr_act(), NULL)), MenuTypes::ALLIANCE_STR[current_index]);
}

void AllianceMenu::update(pros::Controller& controller)
{
    OptionScreen::update(controller);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}