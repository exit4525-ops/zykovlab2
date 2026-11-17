#include "Logger.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

void logAction(const std::string &message)
{
    std::ofstream file("actions.log", std::ios::app);

    if (!file)
    {
        std::cerr << "Cannot open log file" << std::endl;
        return;
    }

    std::time_t now = std::time(nullptr);
    const std::tm *localTime = std::localtime(&now);

    if (localTime != nullptr)
    {
        file << std::put_time(localTime, "%Y-%m-%d %H:%M:%S")
             << " | ";
    }

    file << message << '\n';
}
