#include "Logger.h"
#include "Search.h"

#include <iostream>
#include <cmath>

using namespace std;

vector<int> findPipesByName(const unordered_map<int, Pipe> &pipes)
{
    string name;
    cout << "Enter pipe name or part of name: ";
    getline(cin >> ws, name);
    logAction("Search by name: " + name);

    vector<int> foundIds;

    for (const auto &item : pipes)
    {
        if (item.second.name.find(name) != string::npos)
        {
            cout << "ID: " << item.first << endl;
            printPipe(item.second);
            cout << endl;

            foundIds.push_back(item.first);
        }
    }

    if (foundIds.empty())
    {
        cout << "No pipes found" << endl;
    }

    logAction("Pipe search results: " + to_string(foundIds.size()));
    return foundIds;
}

vector<int> findPipesByRepair(const unordered_map<int, Pipe> &pipes)
{
    int repair;
    cout << "Find pipes under repair? (1-yes/0-no): ";

    while (!(cin >> repair) || (repair != 0 && repair != 1))
    {
        logAction("Invalid input: Wrong value. Enter 1 or 0: ");
        cout << "Wrong value. Enter 1 or 0: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    logAction("Search repair status: " + to_string(repair));
    vector<int> foundIds;

    for (const auto &item : pipes)
    {
        if (item.second.repair == static_cast<bool>(repair))
        {
            cout << "ID: " << item.first << endl;
            printPipe(item.second);
            cout << endl;
            foundIds.push_back(item.first);
        }
    }

    if (foundIds.empty())
    {
        cout << "No pipes found" << endl;
    }
    logAction("Pipe search results: " + to_string(foundIds.size()));
    return foundIds;
}

void findStationsByName(
    const unordered_map<int, CompressorStation> &stations)
{
    string name;
    cout << "Enter station name or part of name: ";
    getline(cin >> ws, name);
    logAction("Search by name: " + name);

    int resultCount = 0;
    bool found = false;

    for (const auto &item : stations)
    {
        if (item.second.name.find(name) != string::npos)
        {
            cout << "ID: " << item.first << endl;
            printCompressorStation(item.second);
            cout << endl;
            found = true;
            resultCount++;
        }
    }

    logAction("Station search results: " + to_string(resultCount));

    if (!found)
    {
        cout << "No stations found" << endl;
    }
}

void findStationsByUnusedPercent(
    const unordered_map<int, CompressorStation> &stations)
{
    double threshold;
    cout << "Enter minimum unused workshops percentage (0-100): ";

    while (!(cin >> threshold) || !isfinite(threshold) ||
           threshold < 0 || threshold > 100)
    {
        logAction("Invalid input: Wrong value. Enter a percentage from 0 to 100: ");
        cout << "Wrong value. Enter a percentage from 0 to 100: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    logAction("Search unused percentage threshold: " + to_string(threshold));
    int resultCount = 0;
    bool found = false;

    for (const auto &item : stations)
    {
        const CompressorStation &station = item.second;

        if (station.workshopCount == 0)
        {
            continue;
        }

        double unusedPercent =
            100.0 * (station.workshopCount - station.workshopsInOperation)
            / station.workshopCount;

        if (unusedPercent >= threshold)
        {
            cout << "ID: " << item.first << endl;
            printCompressorStation(station);
            cout << "Unused workshops: " << unusedPercent << "%" << endl;
            cout << endl;
            found = true;
            resultCount++;
        }
    }

    logAction("Station search results: " + to_string(resultCount));

    if (!found)
    {
        cout << "No stations found" << endl;
    }
}
