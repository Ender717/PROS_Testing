// Included headers
#include "menu/screens/MainMenu.h"
#include "display/lv_objx/lv_btn.h"
#include "menu/MenuTypes.h"

lv_style_t MainMenu::button_released_style;
lv_style_t MainMenu::button_pressed_style;
lv_style_t MainMenu::button_highlighted_style;
lv_style_t MainMenu::button_label_style;

MainMenu::MainMenu()
{
    lv_style_copy(&button_released_style, &lv_style_btn_rel);
    lv_style_copy(&button_pressed_style, &lv_style_btn_pr);
    lv_style_copy(&button_highlighted_style, &lv_style_btn_rel);
    lv_style_copy(&button_label_style, &lv_style_plain);
    button_highlighted_style.body.opa = LV_OPA_TRANSP;
    button_highlighted_style.body.border.color = LV_COLOR_RED;
    button_highlighted_style.body.border.width = 5;
    button_label_style.text.color = LV_COLOR_WHITE;

    createBackground();
    createStartButton();
    createAllianceButton();
    createAutonButton();
    createConfigButton();
    createProfileButton();
    createHighlightButton();
}

MainMenu::~MainMenu()
{

}

lv_res_t MainMenu::startButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::CLOSED);
    return LV_RES_INV;
}

lv_res_t MainMenu::allianceButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::ALLIANCE);
    return LV_RES_INV;
}

lv_res_t MainMenu::autonButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::AUTON);
    return LV_RES_INV;
}

lv_res_t MainMenu::configButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::CONFIG);
    return LV_RES_INV;
}

lv_res_t MainMenu::profileButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    MenuData::getInstance()->setSubmenu(MenuTypes::Submenu::PROFILE);
    return LV_RES_INV;
}

void MainMenu::createBackground()
{
    lv_obj_t* background = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(background, BACKGROUND_FILE);
    lv_obj_set_pos(background, 0, 0);
}

void MainMenu::createStartButton()
{
    // Create the start button
    lv_obj_t* start_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(start_button, LV_BTN_ACTION_CLICK, startButtonEvent);
    lv_btn_set_style(start_button, LV_BTN_STYLE_REL, &button_released_style);
    lv_btn_set_style(start_button, LV_BTN_STYLE_PR, &button_pressed_style);
    lv_obj_set_size(start_button, 200, 110);
    lv_obj_align(start_button, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

    // Create the start button label
    lv_obj_t* start_button_label = lv_label_create(start_button, NULL);
    lv_label_set_text(start_button_label, "START");
    lv_label_set_style(start_button_label, &button_label_style);
}

void MainMenu::createAllianceButton()
{
    // Create the alliance button
    lv_obj_t* alliance_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(alliance_button, LV_BTN_ACTION_CLICK, allianceButtonEvent);
    lv_btn_set_style(alliance_button, LV_BTN_STYLE_REL, &button_released_style);
    lv_btn_set_style(alliance_button, LV_BTN_STYLE_PR, &button_pressed_style);
    lv_obj_set_size(alliance_button, 110, 70);
    lv_obj_align(alliance_button, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 150);

    // Create the alliance button label
    char alliance_text[100];
    int alliance = static_cast<int>(MenuData::getInstance()->getAlliance());
    snprintf(alliance_text, 100, "ALLIANCE\n%s", MenuTypes::ALLIANCE_STR[alliance]);
    lv_obj_t* alliance_button_label = lv_label_create(alliance_button, NULL);
    lv_label_set_text(alliance_button_label, alliance_text);
    lv_label_set_style(alliance_button_label, &button_label_style);
    lv_label_set_align(alliance_button_label, LV_LABEL_ALIGN_CENTER);
}

void MainMenu::createAutonButton()
{
    // Create the auton button
    lv_obj_t* auton_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(auton_button, LV_BTN_ACTION_CLICK, autonButtonEvent);
    lv_btn_set_style(auton_button, LV_BTN_STYLE_REL, &button_released_style);
    lv_btn_set_style(auton_button, LV_BTN_STYLE_PR, &button_pressed_style);
    lv_obj_set_size(auton_button, 110, 70);
    lv_obj_align(auton_button, NULL, LV_ALIGN_IN_TOP_LEFT, 126, 150);

    // Create the auton button label
    char auton_text[100];
    int auton = static_cast<int>(MenuData::getInstance()->getAuton());
    snprintf(auton_text, 100, "AUTON\n%s", MenuTypes::AUTON_STR[auton]);
    lv_obj_t* auton_button_label = lv_label_create(auton_button, NULL);
    lv_label_set_text(auton_button_label, auton_text);
    lv_label_set_style(auton_button_label, &button_label_style);
    lv_label_set_align(auton_button_label, LV_LABEL_ALIGN_CENTER);
}

void MainMenu::createConfigButton()
{
    // Create the config button
    lv_obj_t* config_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(config_button, LV_BTN_ACTION_CLICK, configButtonEvent);
    lv_btn_set_style(config_button, LV_BTN_STYLE_REL, &button_released_style);
    lv_btn_set_style(config_button, LV_BTN_STYLE_PR, &button_pressed_style);
    lv_obj_set_size(config_button, 110, 70);
    lv_obj_align(config_button, NULL, LV_ALIGN_IN_TOP_LEFT, 244, 150);

    // Create the config button label
    char config_text[100];
    int config = static_cast<int>(MenuData::getInstance()->getConfig());
    snprintf(config_text, 100, "CONFIG\n%s", MenuTypes::CONFIG_STR[config]);
    lv_obj_t* config_button_label = lv_label_create(config_button, NULL);
    lv_label_set_text(config_button_label, config_text);
    lv_label_set_style(config_button_label, &button_label_style);
    lv_label_set_align(config_button_label, LV_LABEL_ALIGN_CENTER);
}

void MainMenu::createProfileButton()
{
    // Create the profile button
    lv_obj_t* profile_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(profile_button, LV_BTN_ACTION_CLICK, profileButtonEvent);
    lv_btn_set_style(profile_button, LV_BTN_STYLE_REL, &button_released_style);
    lv_btn_set_style(profile_button, LV_BTN_STYLE_PR, &button_pressed_style);
    lv_obj_set_size(profile_button, 110, 70);
    lv_obj_align(profile_button, NULL, LV_ALIGN_IN_TOP_LEFT, 362, 150);

    // Create the profile button label
    char profile_text[100];
    int profile = static_cast<int>(MenuData::getInstance()->getProfile());
    snprintf(profile_text, 100, "PROFILE\n%s", MenuTypes::PROFILE_STR[profile]);
    lv_obj_t* profile_button_label = lv_label_create(profile_button, NULL);
    lv_label_set_text(profile_button_label, profile_text);
    lv_label_set_style(profile_button_label, &button_label_style);
    lv_label_set_align(profile_button_label, LV_LABEL_ALIGN_CENTER);
}

void MainMenu::createHighlightButton()
{
    lv_obj_t* highlight_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_state(highlight_button, LV_BTN_STATE_INA);
    lv_btn_set_style(highlight_button, LV_BTN_STYLE_INA, &button_highlighted_style);
    lv_obj_set_click(highlight_button, false);
    lv_obj_set_size(highlight_button, 200, 110);
    lv_obj_align(highlight_button, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

    highlighted = Button::START;
}

void MainMenu::moveHighlightLeft()
{
    switch (highlighted)
    {
    case Button::START:
        break;
    case Button::ALLIANCE:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 362, 150);
        highlighted = Button::PROFILE;
        break;
    case Button::AUTON:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 8, 150);
        highlighted = Button::ALLIANCE;
        break;
    case Button::CONFIG:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 126, 150);
        highlighted = Button::AUTON;
        break;
    case Button::PROFILE:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 244, 150);
        highlighted = Button::CONFIG;
        break;
    }
}

void MainMenu::moveHighlightRight()
{
    switch (highlighted)
    {
    case Button::START:
        break;
    case Button::ALLIANCE:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 126, 150);
        highlighted = Button::AUTON;
        break;
    case Button::AUTON:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 244, 150);
        highlighted = Button::CONFIG;
        break;
    case Button::CONFIG:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 362, 150);
        highlighted = Button::PROFILE;
        break;
    case Button::PROFILE:
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 8, 150);
        highlighted = Button::ALLIANCE;
        break;
    }
}

void MainMenu::moveHighlightUp()
{
    if (highlighted == Button::START)
    {
        lv_obj_set_size(lv_obj_get_child(lv_scr_act(), NULL), 110, 70);
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 8, 150);
        highlighted = Button::ALLIANCE;
        highlighted = Button::ALLIANCE;
    }
    else
    {
        lv_obj_set_size(lv_obj_get_child(lv_scr_act(), NULL), 200, 110);
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);
        highlighted = Button::START;
    }
}

void MainMenu::moveHighlightDown()
{
    if (highlighted == Button::START)
    {
        lv_obj_set_size(lv_obj_get_child(lv_scr_act(), NULL), 110, 70);
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 8, 150);
        highlighted = Button::ALLIANCE;
        highlighted = Button::ALLIANCE;
    }
    else
    {
        lv_obj_set_size(lv_obj_get_child(lv_scr_act(), NULL), 200, 110);
        lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);
        highlighted = Button::START;
    }
}

void MainMenu::pressButton()
{
    switch (highlighted)
    {
        case Button::START:
            startButtonEvent(lv_obj_get_child(lv_scr_act(), NULL));
            break;
        case Button::ALLIANCE:
            allianceButtonEvent(lv_obj_get_child(lv_scr_act(), NULL));
            break;
        case Button::AUTON:
            autonButtonEvent(lv_obj_get_child(lv_scr_act(), NULL));
            break;
        case Button::CONFIG:
            configButtonEvent(lv_obj_get_child(lv_scr_act(), NULL));
            break;
        case Button::PROFILE:
            profileButtonEvent(lv_obj_get_child(lv_scr_act(), NULL));
            break;
    }
}

void MainMenu::update(pros::Controller& controller)
{
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
        moveHighlightLeft();
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
        moveHighlightRight();
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
        moveHighlightUp();
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
        moveHighlightDown();

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        pressButton();
}