// Inclusion guard
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

// Included libraries
#include <string>
#include <vector>

// Included headers
#include "main.h"

/**
 * This class manages the tasks running in the system
 * @author Nathan Sandvig
 */
class TaskManager
{
private:
    /**
     * The controlled instance
     */
    static TaskManager* instance;

    /**
     * The tasks being managed
     */
    std::vector<pros::Task*> tasks;

    /**
     * Private constructor to prevent uncontrolled construction
     */
    TaskManager();

public:
    /**
     * Remove the copy constructor
     */
    TaskManager(const TaskManager& copy) = delete;

    /**
     * Remove the assignment operator
     */
    TaskManager& operator=(const TaskManager& rhs) = delete;

    /**
     * Destructor
     */
    ~TaskManager();

    /**
     * Gets the controlled instance
     * @return The controlled instance
     */
    static TaskManager* getInstance();

    /**
     * Adds a task to the manager
     * @param task The task being added
     */
    void addTask(pros::Task* task);

    /**
     * Removes a task from the manager
     * @param taskName The name of the task being removed
     */
    void removeTask(std::string taskName);

    /**
     * Gets a task from the manager
     * @param taskName The name of the task
     * @return The task
     */
    pros::Task* getTask(std::string taskName);

    /**
     * Suspends all tasks
     */
    void suspendAll();

    /**
     * Resumes all tasks
     */
    void resumeAll();

    /**
     * Removes all tasks
     */
    void removeAll();
};

#endif