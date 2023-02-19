// Included headers
#include "menu/screens/AllianceMenu.h"

lv_style_t AllianceMenu::button_matrix_background_style;
lv_style_t AllianceMenu::button_released_style;
lv_style_t AllianceMenu::button_pressed_style;
lv_style_t AllianceMenu::button_highlighted_style;

AllianceMenu::AllianceMenu()
{
    lv_style_copy(&button_matrix_background_style, &lv_style_transp);
    lv_style_copy(&button_released_style, &lv_style_btn_rel);
    lv_style_copy(&button_pressed_style, &lv_style_btn_pr);
    lv_style_copy(&button_highlighted_style, &lv_style_transp);
    button_released_style.text.color = LV_COLOR_WHITE;
    button_pressed_style.text.color = LV_COLOR_WHITE;
    button_highlighted_style.body.border.color = LV_COLOR_RED;
    button_highlighted_style.body.border.width = 5;

    background = nullptr;
    button_matrix = nullptr;
    highlight_button = nullptr;

    currentIndex = 0;
}

AllianceMenu::~AllianceMenu()
{
    if (background != nullptr)
    {
        delete background;
        background = nullptr;
    }
    if (button_matrix != nullptr)
    {
        delete button_matrix;
        button_matrix = nullptr;
    }
    if (highlight_button != nullptr)
    {
        delete highlight_button;
        highlight_button = nullptr;
    }
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

void AllianceMenu::createBackground()
{
    if (background != nullptr)
    {
        delete background;
        background = nullptr;
    }

    background = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(background, BACKGROUND_FILE);
    lv_obj_set_pos(background, 0, 0);
}

void AllianceMenu::createButtonMatrix()
{
    if (button_matrix != nullptr)
    {
        delete button_matrix;
        button_matrix = nullptr;
    }

    // Create the button map
    int button_map_size = MenuTypes::ALLIANCE_COUNT + ((MenuTypes::ALLIANCE_COUNT - 1) / BUTTONS_PER_LINE) + 1;
    const char** button_map = new const char*[button_map_size];
    for (int i = 0; i < button_map_size - 1; i++)
    {
        if ((i + 1) % (BUTTONS_PER_LINE + 1) == 0)
            button_map[i] = "\n";
        else
        {
            int strIndex = i - (i / (BUTTONS_PER_LINE + 1));
            button_map[i] = MenuTypes::ALLIANCE_STR[strIndex];
        }
    }
    button_map[button_map_size - 1] = "";

    // Create the button matrix
    button_matrix = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BG, &button_matrix_background_style);
    lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BTN_REL, &button_released_style);
    lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BTN_PR, &button_pressed_style);
    lv_btnm_set_map(button_matrix, button_map);
    lv_btnm_set_action(button_matrix, buttonEvent);
    lv_obj_set_size(button_matrix, BUTTON_MATRIX_WIDTH, BUTTON_MATRIX_HEIGHT);
    lv_obj_align(button_matrix, NULL, LV_ALIGN_IN_TOP_LEFT, BUTTON_MATRIX_X, BUTTON_MATRIX_Y);
}

void AllianceMenu::createHighlightButton()
{
    if (highlight_button != nullptr)
    {
        delete highlight_button;
        highlight_button = nullptr;
    }

    // Create the highlight button
    highlight_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_state(highlight_button, LV_BTN_STATE_INA);
    lv_btn_set_style(highlight_button, LV_BTN_STYLE_INA, &button_highlighted_style);
    lv_obj_set_click(highlight_button, false);

    // Place the highlight button
    if (button_matrix != nullptr)
    {
        int width = (BUTTON_MATRIX_WIDTH - ((BUTTONS_PER_LINE - 1) * button_matrix->style_p->body.padding.inner)) / BUTTONS_PER_LINE;
        int height = (BUTTON_MATRIX_HEIGHT - (((MenuTypes::ALLIANCE_COUNT / BUTTONS_PER_LINE) - 1) * button_matrix->style_p->body.padding.inner)) /
            (MenuTypes::ALLIANCE_COUNT / BUTTONS_PER_LINE);
        int x = 0;
        int y = 0;
        lv_obj_set_size(highlight_button, width, height);
        lv_obj_align(highlight_button, button_matrix, LV_ALIGN_IN_TOP_LEFT, x, y);
    }
}