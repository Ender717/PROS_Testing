// Included headers
#include "utils/Database.h"

Database::Database()
{
    writing = 0;
    reading = 0;
}

void Database::addReader()
{
    TaskManager* taskManager = TaskManager::getInstance();
    if (writing == 0 && writers.empty())
        reading++;
    else
    {
        std::string taskName = pros::Task::current().get_name();
        readers.push_back(taskName);
        taskManager->getTask(taskName)->suspend();
    }
}

void Database::addWriter()
{
    TaskManager* taskManager = TaskManager::getInstance();
    if (writing == 0 && reading == 0)
        writing++;
    else
    {
        std::string taskName = pros::Task::current().get_name();
        writers.push_back(taskName);
        taskManager->getTask(taskName)->suspend();
    }
}

void Database::removeReader()
{
    TaskManager* taskManager = TaskManager::getInstance();
    reading--;
    if (reading == 0 && !writers.empty())
    {
        taskManager->getTask(writers.front())->resume();
        writers.erase(writers.begin());
        writing++;
    }
}

void Database::removeWriter()
{
    TaskManager* taskManager = TaskManager::getInstance();
    writing--;
    if (writing == 0)
    {
        if (!writers.empty())
        {
            taskManager->getTask(writers.front())->resume();
            writers.erase(writers.begin());
            writing++;
        }
        else if (!readers.empty())
        {
            for (std::string taskName : readers)
            {
                taskManager->getTask(taskName)->resume();
                reading++;
            }
            readers.clear();
        }
    }
}