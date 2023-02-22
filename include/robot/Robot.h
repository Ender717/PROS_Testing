// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included headers

/**
 * This class manages a singleton robot
 * @author Nathan Sandvig
 */
class Robot
{
private:
    /**
     * The singleton instance of the robot
     */
    static Robot* instance;

    /**
     * Private constructor to prevent uncontrolled construction
     */
    Robot();

public:
    /**
     * Remove the copy constructor
     */
    Robot(const Robot& copy) = delete;

    /**
     * Remove the assignment operator
     */
    Robot& operator=(const Robot& rhs) = delete;

    /**
     * Gets the singleton instance of the robot
     */
    static Robot* getInstance();
};

#endif