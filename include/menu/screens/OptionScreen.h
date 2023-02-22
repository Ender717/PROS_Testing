// Inclusion guard
#ifndef OPTION_SCREEN_H
#define OPTION_SCREEN_H

// Included headers
#include "MenuScreen.h"

/**
 * This class manages any menu screen which handles option selection
 * @author Nathan Sandvig
 */
class OptionScreen : public MenuScreen
{
protected:
    /**
     * The configuration info for the button matrix
     */
    static constexpr int BUTTON_MATRIX_WIDTH = 460;
    static constexpr int BUTTON_MATRIX_HEIGHT = 180;
    static constexpr int BUTTON_MATRIX_X = 10;
    static constexpr int BUTTON_MATRIX_Y = 50;
    static constexpr int BUTTON_MATRIX_PADDING = 5;

    /**
     * The object styles
     */
    static lv_style_t button_matrix_background_style;
    static lv_style_t button_released_style;
    static lv_style_t button_pressed_style;
    static lv_style_t button_highlighted_style;

    /**
     * The number of buttons per line for the button matrix
     */
    int buttons_per_line;

    /**
     * The index of the currently highlighted button
     */
    int current_index;

    /**
     * The number of labels in the button matrix
     */
    int matrix_label_count;

    /**
     * Methods to create each component of the menu screen
     */
    void createBackground(const char* background_file);
    void createButtonMatrix(const char* matrix_labels[]);
    void createHighlightButton();

    /**
     * Methods to interact with the highlighted button
     */
    void placeHighlight();
    void moveHighlightLeft();
    void moveHighlightRight();
    void moveHighlightUp();
    void moveHighlightDown();

public:
    /**
     * Parameterized constructor
     */
    OptionScreen(const char* background_file, const char* matrix_labels[], int _matrix_label_count, int _buttons_per_line, int _current_index);

    /**
     * Destructor
     */
    ~OptionScreen();

    /**
     * Updates the menu screen
     * @param controller The input controller
     */
    virtual void update(pros::Controller& controller);
};

#endif