// Included headers
#include "utils/TaskManager.h"

TaskManager* TaskManager::instance = nullptr;

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{
    instance = nullptr;
    for (pros::Task* task : tasks)
    {
        task->remove();
        delete task;
    }
}

TaskManager* TaskManager::getInstance()
{
    if (instance == nullptr)
        instance = new TaskManager;
    return instance;
}

void TaskManager::addTask(pros::Task* task)
{
    tasks.push_back(task);
}

void TaskManager::removeTask(std::string taskName)
{
    int index = -1;
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->get_name() == taskName)
            index = i;
    if (index != -1)
    {
        pros::Task* temp = tasks[index];
        tasks.erase(tasks.begin() + index);
        temp->remove();
        delete temp;
    }
}

pros::Task* TaskManager::getTask(std::string taskName)
{
    int index = -1;
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->get_name() == taskName)
            index = i;

    pros::Task* task = nullptr;
    if (index != -1)
        task = tasks[index];
    return task;
}

void TaskManager::suspendAll()
{
    for (pros::Task* task : tasks)
        task->suspend();
}

void TaskManager::resumeAll()
{
    for (pros::Task* task : tasks)
        task->resume();
}

void TaskManager::removeAll()
{
    for (pros::Task* task : tasks)
    {
        task->remove();
        delete task;
    }
    tasks.clear();
}