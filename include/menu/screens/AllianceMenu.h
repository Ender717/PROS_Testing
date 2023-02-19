// Inclusion guard
#ifndef ALLIANCE_MENU_H
#define ALLIANCE_MENU_H

// Included headers
#include "MenuScreen.h"

class AllianceMenu : public MenuScreen
{
private:
    /**
     * The name of the file containing the background for the main menu
     */
    static constexpr char BACKGROUND_FILE[50] = "S:/usd/images/alliance_menu.bin";

    /**
     * The configuration info for the button matrix
     */
    static constexpr int BUTTONS_PER_LINE = 2;
    static constexpr int BUTTON_MATRIX_WIDTH = 460;
    static constexpr int BUTTON_MATRIX_HEIGHT = 180;
    static constexpr int BUTTON_MATRIX_X = 10;
    static constexpr int BUTTON_MATRIX_Y = 50;

    /**
     * The object styles
     */
    static lv_style_t button_matrix_background_style;
    static lv_style_t button_released_style;
    static lv_style_t button_pressed_style;
    static lv_style_t button_highlighted_style;

    /**
     * The lvgl objects used to draw the alliance menu screen
     */
    lv_obj_t* background;
    lv_obj_t* button_matrix;
    lv_obj_t* highlight_button;

    /**
     * The index of the currently highlighted button
     */
    int currentIndex;

    /**
     * The event for the buttons
     * @param button_matrix The matrix containing the buttons
     * @param text The text on the button which was pressed
     */
    static lv_res_t buttonEvent(lv_obj_t* button_matrix, const char* text);

    /**
     * Methods to create each component of the menu screen
     */
    void createBackground();
    void createButtonMatrix();
    void createHighlightButton();

    /**
     * Methods to interact with the highlighted button
     */
    void moveHighlightLeft();
    void moveHighlightRight();
    void moveHighlightUp();
    void moveHighlightDown();
    void pressButton();

public:
    /**
     * Default constructor
     */
    AllianceMenu();

    /**
     * Destructor
     */
    virtual ~AllianceMenu();

    /**
     * Opens the menu screen
     */
    virtual void open();

    /**
     * Closes the menu screen
     */
    virtual void close();

    /**
     * Updates the menu screen
     * @param controller The input controller
     */
    virtual void update(pros::Controller controller);
};

#endif