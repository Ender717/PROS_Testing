// Included headers
#include "utils/Database.h"

Database::Database()
{
    writing = 0;
    reading = 0;
}

Database::~Database()
{
    for (pros::Task* task : writers)
    {
        task->remove();
        delete task;
    }

    for (pros::Task* task : readers)
    {
        task->remove();
        delete task;
    }
}

void Database::addReader()
{
    if (writing == 0 && writers.empty())
        reading++;
    else
    {
        pros::Task task = pros::Task::current();
        readers.push_back(&task);
        task.suspend();
    }
}

void Database::addWriter()
{
    if (writing == 0 && reading == 0)
        writing++;
    else
    {
        pros::Task task = pros::Task::current();
        writers.push_back(&task);
        task.suspend();
    }
}

void Database::removeReader()
{
    reading--;
    if (reading == 0 && !writers.empty())
    {
        writers.front()->resume();
        writers.erase(writers.begin());
        writing++;
    }
}

void Database::removeWriter()
{
    writing--;
    if (writing == 0)
    {
        if (!writers.empty())
        {
            writers.front()->resume();
            writers.erase(writers.begin());
            writing++;
        }
        else if (!readers.empty())
        {
            for (pros::Task* task : readers)
            {
                task->resume();
                reading++;
            }
            readers.clear();
        }
    }
}