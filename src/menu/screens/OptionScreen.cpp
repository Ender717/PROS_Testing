// Included headers
#include "menu/screens/OptionScreen.h"

lv_style_t OptionScreen::button_matrix_background_style;
lv_style_t OptionScreen::button_released_style;
lv_style_t OptionScreen::button_pressed_style;
lv_style_t OptionScreen::button_highlighted_style;

OptionScreen::OptionScreen(const char* background_file, const char* matrix_labels[], int _matrix_label_count, int _buttons_per_line, int _current_index)
{
    lv_style_copy(&button_matrix_background_style, &lv_style_transp);
    lv_style_copy(&button_released_style, &lv_style_btn_rel);
    lv_style_copy(&button_pressed_style, &lv_style_btn_pr);
    lv_style_copy(&button_highlighted_style, &lv_style_btn_rel);
    button_released_style.text.color = LV_COLOR_WHITE;
    button_pressed_style.text.color = LV_COLOR_WHITE;
    button_highlighted_style.body.opa = LV_OPA_TRANSP;
    button_highlighted_style.body.border.color = LV_COLOR_RED;
    button_highlighted_style.body.border.width = 5;

    matrix_label_count = _matrix_label_count;
    buttons_per_line = _buttons_per_line;
    current_index = _current_index;
    createBackground(background_file);
    createButtonMatrix(matrix_labels);
    createHighlightButton();
}

OptionScreen::~OptionScreen()
{
    lv_obj_clean(lv_scr_act());
}

void OptionScreen::createBackground(const char* background_file)
{
    lv_obj_t* background = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(background, background_file);
    lv_obj_set_pos(background, 0, 0);
}

void OptionScreen::createButtonMatrix(const char* matrix_map[])
{
    // Create the button map
    int button_map_size = matrix_label_count + ((matrix_label_count - 1) / buttons_per_line) + 1;
    const char** button_map = new const char*[button_map_size];
    for (int i = 0; i < button_map_size - 1; i++)
    {
        if ((i + 1) % (buttons_per_line + 1) == 0)
            button_map[i] = "\n";
        else
        {
            int strIndex = i - (i / (buttons_per_line + 1));
            button_map[i] = matrix_map[strIndex];
        }
    }
    button_map[button_map_size - 1] = "";

    // Create the button matrix
    lv_obj_t* button_matrix = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BG, &button_matrix_background_style);
    lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BTN_REL, &button_released_style);
    lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BTN_PR, &button_pressed_style);
    lv_btnm_set_map(button_matrix, button_map);
    lv_obj_set_size(button_matrix, BUTTON_MATRIX_WIDTH, BUTTON_MATRIX_HEIGHT);
    lv_obj_align(button_matrix, NULL, LV_ALIGN_IN_TOP_LEFT, BUTTON_MATRIX_X, BUTTON_MATRIX_Y);
    button_matrix->style_p->body.padding.hor = BUTTON_MATRIX_PADDING;
    button_matrix->style_p->body.padding.ver = BUTTON_MATRIX_PADDING;
    button_matrix->style_p->body.padding.inner = BUTTON_MATRIX_PADDING;
}

void OptionScreen::createHighlightButton()
{
    // Create the highlight button
    lv_obj_t* highlight_button = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_state(highlight_button, LV_BTN_STATE_INA);
    lv_btn_set_style(highlight_button, LV_BTN_STYLE_INA, &button_highlighted_style);
    lv_obj_set_click(highlight_button, false);

    // Place the highlight button
    placeHighlight();
}

void OptionScreen::placeHighlight()
{
    int row = current_index / buttons_per_line;
    int columns;
    if (row == (matrix_label_count - 1) / buttons_per_line)
        columns = ((matrix_label_count - 1) % buttons_per_line) + 1;
    else
        columns = buttons_per_line;

    int matrix_width = BUTTON_MATRIX_WIDTH - (2 * BUTTON_MATRIX_PADDING);
    int width_padding = (columns - 1) * BUTTON_MATRIX_PADDING;
    int width = (matrix_width - width_padding) / columns;

    int matrix_height = BUTTON_MATRIX_HEIGHT - (2 * BUTTON_MATRIX_PADDING);
    int lines = ((matrix_label_count - 1) / buttons_per_line) + 1;
    int height_padding = (lines - 1) * BUTTON_MATRIX_PADDING;
    int height = (matrix_height - height_padding) / lines;

    int x = BUTTON_MATRIX_X + ((current_index % buttons_per_line) * (width + BUTTON_MATRIX_PADDING)) + BUTTON_MATRIX_PADDING;
    int y = BUTTON_MATRIX_Y + ((current_index / buttons_per_line) * (height + BUTTON_MATRIX_PADDING)) + BUTTON_MATRIX_PADDING;

    lv_obj_set_size(lv_obj_get_child(lv_scr_act(), NULL), width, height);
    lv_obj_align(lv_obj_get_child(lv_scr_act(), NULL), lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, x, y);
}

void OptionScreen::moveHighlightLeft()
{
    int row = current_index / buttons_per_line;
    int column = current_index % buttons_per_line;

    column--;
    if (column < 0)
    {
        if (row == (matrix_label_count - 1) / buttons_per_line)
            column = (matrix_label_count - 1) % buttons_per_line;
        else
            column = buttons_per_line - 1;
    }

    current_index = (row * buttons_per_line) + column;

    placeHighlight();
}

void OptionScreen::moveHighlightRight()
{
    int row = current_index / buttons_per_line;
    int column = current_index % buttons_per_line;

    column++;
    if (row == (matrix_label_count - 1) / buttons_per_line)
    {
        if (column > (matrix_label_count - 1) % buttons_per_line)
            column = 0;
    }
    else
    {
        if (column > buttons_per_line - 1)
            column = 0;
    }

    current_index = (row * buttons_per_line) + column;

    placeHighlight();
}

void OptionScreen::moveHighlightUp()
{
    int row = current_index / buttons_per_line;
    int column = current_index % buttons_per_line;

    row--;
    if (row < 0)
        row = (matrix_label_count - 1) / buttons_per_line;

    if (row == (matrix_label_count - 1) / buttons_per_line)
        column = std::min(column, (matrix_label_count - 1) % buttons_per_line);

    current_index = (row * buttons_per_line) + column;

    placeHighlight();
}

void OptionScreen::moveHighlightDown()
{
    int row = current_index / buttons_per_line;
    int column = current_index % buttons_per_line;

    row++;
    if (row > (matrix_label_count - 1) / buttons_per_line)
        row = 0;

    if (row == (matrix_label_count - 1) / buttons_per_line)
        column = std::min(column, (matrix_label_count - 1) % buttons_per_line);

    current_index = (row * buttons_per_line) + column;

    placeHighlight();
}

void OptionScreen::update(pros::Controller& controller)
{
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
        moveHighlightLeft();
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
        moveHighlightRight();
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
        moveHighlightUp();
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
        moveHighlightDown();
}