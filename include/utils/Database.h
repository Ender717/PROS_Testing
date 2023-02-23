// Inclusion guard
#ifndef DATABASE_H
#define DATABASE_H

// Included libraries
#include <vector>

// Included headers
#include "main.h"
#include "TaskManager.h"

/**
 * This class manages a classical database thread manager
 * @author Nathan Sandvig
 */
class Database
{
private:
    /**
     * Names of tasks waiting to write
     */
    std::vector<std::string> writers;

    /**
     * Names of tasks waiting to read
     */
    std::vector<std::string> readers;

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