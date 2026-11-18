#include "Logger.h"
#include "Storage.h"

#include <iostream>

using namespace std;

void savePipe(ofstream &file, const Pipe &pipe)
{
    file << pipe.name << endl;
    file << pipe.length << endl;
    file << pipe.diameter << endl;
    file << pipe.repair << endl;
}

void saveStation(ofstream &file, const CompressorStation &station)
{
    file << station.name << endl;
    file << station.workshopCount << endl;
    file << station.workshopsInOperation << endl;
    file << station.stationClass << endl;
}

bool readPipe(ifstream &file, Pipe &pipe)
{
    Pipe loadedPipe;

    if (!(file >> loadedPipe.name >> loadedPipe.length
               >> loadedPipe.diameter >> loadedPipe.repair) ||
        loadedPipe.length <= 0 || loadedPipe.diameter <= 0)
    {
        return false;
    }

    pipe = loadedPipe;
    return true;
}

bool readStation(ifstream &file, CompressorStation &station)
{
    CompressorStation loadedStation;

    if (!(file >> loadedStation.name >> loadedStation.workshopCount
               >> loadedStation.workshopsInOperation >> loadedStation.stationClass) ||
        loadedStation.workshopCount < 0 ||
        loadedStation.workshopsInOperation < 0 ||
        loadedStation.workshopsInOperation > loadedStation.workshopCount ||
        loadedStation.stationClass < 0)
    {
        return false;
    }

    station = loadedStation;
    return true;
}

void saveData(const unordered_map<int, Pipe> &pipes,
              const unordered_map<int, CompressorStation> &stations,
              int nextId)
{
    string filename;
    cout << "Enter filename: ";
    getline(cin >> ws, filename);
    logAction("File requested: " + filename);

    ofstream file(filename);

    if (!file)
    {
        logAction("File error: " + filename);
        cout << "File error" << endl;
        return;
    }

    file << nextId << '\n';

    file << pipes.size() << '\n';

    for (const auto &item : pipes)
    {
        file << item.first << '\n';
        savePipe(file, item.second);
    }

    file << stations.size() << '\n';

    for (const auto &item : stations)
    {
        file << item.first << '\n';
        saveStation(file, item.second);
    }

    file.close();

    if (!file)
    {
        logAction("File error: " + filename);
        cout << "File error" << endl;
        return;
    }

    logAction("Data saved: " + filename);

    cout << "Data saved" << endl;
}

bool loadData(unordered_map<int, Pipe> &pipes,
              unordered_map<int, CompressorStation> &stations,
              int &nextId)
{
    string filename;
    cout << "Enter filename: ";
    getline(cin >> ws, filename);
    logAction("File requested: " + filename);

    ifstream file(filename);

    if (!file)
    {
        logAction("File not found: " + filename);
        cout << "File not found" << endl;
        return false;
    }

    unordered_map<int, Pipe> loadedPipes;
    unordered_map<int, CompressorStation> loadedStations;

    int loadedNextId;
    int pipeCount;
    int stationCount;

    if (!(file >> loadedNextId >> pipeCount) ||
        loadedNextId <= 0 || pipeCount < 0)
    {
        logAction("Invalid data: " + filename);
        cout << "Invalid data" << endl;
        return false;
    }

    for (int i = 0; i < pipeCount; i++)
    {
        int id;
        Pipe pipe;

        if (!(file >> id) || id <= 0 || id >= loadedNextId ||
            !readPipe(file, pipe))
        {
            logAction("Invalid pipe data: " + filename);
            cout << "Invalid pipe data" << endl;
            return false;
        }

        if (!loadedPipes.emplace(id, pipe).second)
        {
            logAction("Duplicate ID: " + filename);
            cout << "Duplicate ID" << endl;
            return false;
        }
    }

    if (!(file >> stationCount) || stationCount < 0)
    {
        logAction("Invalid data: " + filename);
        cout << "Invalid data" << endl;
        return false;
    }

    for (int i = 0; i < stationCount; i++)
    {
        int id;
        CompressorStation station;

        if (!(file >> id) || id <= 0 || id >= loadedNextId ||
            !readStation(file, station))
        {
            logAction("Invalid station data: " + filename);
            cout << "Invalid station data" << endl;
            return false;
        }

        if (loadedPipes.find(id) != loadedPipes.end() ||
            !loadedStations.emplace(id, station).second)
        {
            logAction("Duplicate ID: " + filename);
            cout << "Duplicate ID" << endl;
            return false;
        }
    }

    pipes.swap(loadedPipes);
    stations.swap(loadedStations);
    nextId = loadedNextId;

    logAction("Data loaded: " + filename);

    cout << "Data loaded" << endl;
    return true;
}
