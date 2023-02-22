// Inclusion guard
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

// Included headers
#include "MenuScreen.h"

/**
 * This class manages the main menu screen
 * @author Nathan Sandvig
 */
class MainMenu : public MenuScreen
{
private:
    /**
     * The buttons in the main menu screen
     */
    enum class Button
    {
        START,
        ALLIANCE,
        AUTON,
        CONFIG,
        PROFILE
    };

    /**
     * The name of the file containing the logo for the main menu
     */
    static constexpr char BACKGROUND_FILE[50] = "S:/usd/images/main_menu.bin";

    /**
     * The button styles
     */
    static lv_style_t button_released_style;
    static lv_style_t button_pressed_style;
    static lv_style_t button_highlighted_style;
    static lv_style_t button_label_style;

    /**
     * The currently highlighted button
     */
    Button highlighted;

    /**
     * The events for the buttons
     * @param button The button which was pressed
     */
    static lv_res_t startButtonEvent(lv_obj_t* button);
    static lv_res_t allianceButtonEvent(lv_obj_t* button);
    static lv_res_t autonButtonEvent(lv_obj_t* button);
    static lv_res_t configButtonEvent(lv_obj_t* button);
    static lv_res_t profileButtonEvent(lv_obj_t* button);

    /**
     * Methods to create each component of the menu screen
     */
    void createBackground();
    void createStartButton();
    void createAllianceButton();
    void createAutonButton();
    void createConfigButton();
    void createProfileButton();
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
    MainMenu();

    /**
     * Destructor
     */
    virtual ~MainMenu();

    /**
     * Updates the main menu
     * @param controller The input controller
     */
    virtual void update(pros::Controller& controller);
};

#endif