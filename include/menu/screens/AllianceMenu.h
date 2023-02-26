// Inclusion guard
#ifndef ALLIANCE_MENU_H
#define ALLIANCE_MENU_H

// Included headers
#include "OptionScreen.h"

/**
 * This class manages the alliance menu screen
 * @author Nathan Sandvig
 */
class AllianceMenu : public OptionScreen
{
private:
    /**
     * The name of the file containing the background for the alliance menu
     */
    static constexpr char BACKGROUND_FILE[50] = "S:/usd/images/alliance_menu.bin";

    /**
     * The configuration info for the button matrix
     */
    static constexpr int BUTTONS_PER_LINE = 2;

    /**
     * The event for the buttons
     * @param button_matrix The matrix containing the buttons
     * @param text The text on the button which was pressed
     */
    static lv_res_t buttonEvent(lv_obj_t* button_matrix, const char* text);

    /**
     * Methods to interact with the highlighted button
     */
    void pressButton();

public:
    /**
     * Default constructor
     */
    AllianceMenu();

    /**
     * Updates the menu screen
     * @param controller The input controller
     */
    virtual void update(pros::Controller& controller);
};

#endif