// Inclusion guard
#ifndef DATABASE_H
#define DATABASE_H

// Included libraries
#include <vector>

// Included headers
#include "main.h"

/**
 * This class manages a classical database thread manager
 * @author Nathan Sandvig
 */
class Database
{
private:
    /**
     * Tasks waiting to write
     */
    std::vector<pros::Task*> writers;

    /**
     * Tasks waiting to read
     */
    std::vector<pros::Task*> readers;

    /**
     * The number of tasks writing data
     */
    int writing;

    /**
     * The number of tasks reading data
     */
    int reading;

public:
    /**
     * Default constructor
     */
    Database();

    /**
     * Destructor
     */
    ~Database();

    /**
     * Adds a reader task to the database
     * @param task The reader task
     */
    void addReader();

    /**
     * Adds a writer task to the database
     * @param task The writer task
     */
    void addWriter();

    /**
     * Removes a reader task from the database
     */
    void removeReader();

    /**
     * Removes a writer task from the database
     */
    void removeWriter();
};

#endif