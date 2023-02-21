// Inclusion guard
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

// Included headers
#include "MenuScreen.h"

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
    static constexpr char LOGO_FILE[50] = "S:/usd/images/main_logo.bin";

    /**
     * The button styles
     */
    static lv_style_t button_released_style;
    static lv_style_t button_pressed_style;
    static lv_style_t button_highlighted_style;
    static lv_style_t button_label_style;

    /**
     * The lvgl objects used to draw the main menu screen
     */
    lv_obj_t* logo;
    lv_obj_t* start_button;
    lv_obj_t* start_button_label;
    lv_obj_t* alliance_button;
    lv_obj_t* alliance_button_label;
    lv_obj_t* auton_button;
    lv_obj_t* auton_button_label;
    lv_obj_t* config_button;
    lv_obj_t* config_button_label;
    lv_obj_t* profile_button;
    lv_obj_t* profile_button_label;

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
    void createLogo();
    void createStartButton();
    void createAllianceButton();
    void createAutonButton();
    void createConfigButton();
    void createProfileButton();

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