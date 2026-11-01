#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map> 

using namespace std;

struct Pipe
{
    string name;
    double length;
    int diameter;
    bool repair;
};

struct CompressorStation
{
    string name;
    int workshopCount;
    int workshopsInOperation;
    int stationClass;
};


// ввод трубы
Pipe inputPipe()
{
    Pipe pipe;

    cout << "Enter pipe name: ";
    cin >> pipe.name;

    cout << "Enter pipe length (km): ";

    while (!(cin >> pipe.length) || pipe.length <= 0)
    {
        cout << "Wrong value. Enter length again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter pipe diameter (mm): ";

    while (!(cin >> pipe.diameter) || pipe.diameter <= 0)
    {
        cout << "Wrong value. Enter diameter again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    int repairValue;

    cout << "Is pipe under repair? (1-y/0-n): ";

    while (!(cin >> repairValue) ||
           (repairValue != 0 && repairValue != 1))
    {
        cout << "Wrong value. Enter 1 or 0: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    pipe.repair = repairValue;

    return pipe;
}


// ввод станции
CompressorStation inputStation()
{
    CompressorStation station;

    cout << "Enter station name: ";
    cin >> station.name;

    cout << "Enter number of workshops: ";

    while (!(cin >> station.workshopCount) ||
           station.workshopCount < 0)
    {
        cout << "Wrong value. Enter number of workshops again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter number of workshops in operation: ";

    while (!(cin >> station.workshopsInOperation) ||
           station.workshopsInOperation < 0 ||
           station.workshopsInOperation > station.workshopCount)
    {
        cout << "Wrong value. Enter number of workshops in operation again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter station class: ";

    while (!(cin >> station.stationClass) ||
           station.stationClass < 0)
    {
        cout << "Wrong value. Enter station class again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    return station;
}


// вывод трубы
void printPipe(Pipe pipe)
{
    cout << "--- Pipe ---" << endl;
    cout << "Name: " << pipe.name << endl;
    cout << "Length: " << pipe.length << " km" << endl;
    cout << "Diameter: " << pipe.diameter << " mm" << endl;

    if (pipe.repair)
    {
        cout << "Repair: Yes" << endl;
    }
    else
    {
        cout << "Repair: No" << endl;
    }
}


// изменение статуса ремонта трубы
void editPipe(Pipe &pipe)
{
    pipe.repair = !pipe.repair;
}


// вывод станции
void printCompressorStation(CompressorStation station)
{
    cout << "--- Compressor Station ---" << endl;
    cout << "Name: " << station.name << endl;
    cout << "Workshops: " << station.workshopCount << endl;
    cout << "Workshops in operation: "
         << station.workshopsInOperation << endl;
    cout << "Station class: " << station.stationClass << endl;
}


// запуск/останов цеха
void editStation(CompressorStation &station)
{
    int choice;

    cout << "1. Start workshop" << endl;
    cout << "2. Stop workshop" << endl;
    cout << "Enter choice: ";

    while (!(cin >> choice) ||
           (choice != 1 && choice != 2))
    {
        cout << "Wrong number. Input new choice: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (choice == 1)
    {
        if (station.workshopsInOperation < station.workshopCount)
        {
            station.workshopsInOperation++;
            cout << "Workshop started" << endl;
        }
        else
        {
            cout << "All workshops are already working" << endl;
        }
    }
    else
    {
        if (station.workshopsInOperation > 0)
        {
            station.workshopsInOperation--;
            cout << "Workshop stopped" << endl;
        }
        else
        {
            cout << "No working workshops" << endl;
        }
    }
}


// сохранение трубы в уже открытый файл
void savePipe(ofstream &file, Pipe pipe)
{
    file << pipe.name << endl;
    file << pipe.length << endl;
    file << pipe.diameter << endl;
    file << pipe.repair << endl;
}


// сохранение станции в уже открытый файл
void saveStation(ofstream &file, CompressorStation station)
{
    file << station.name << endl;
    file << station.workshopCount << endl;
    file << station.workshopsInOperation << endl;
    file << station.stationClass << endl;
}


// отдельное сохранение трубы
void savePipeToFile(Pipe pipe)
{
    ofstream file("Pipedata.txt");

    if (!file)
    {
        cout << "File error" << endl;
        return;
    }

    savePipe(file, pipe);
    file.close();

    if (!file)
    {
        cout << "File error" << endl;
        return;
    }

    cout << "Pipe saved" << endl;
}


// отдельное сохранение станции
void saveStationToFile(CompressorStation station)
{
    ofstream file("Stationdata.txt");

    if (!file)
    {
        cout << "File error" << endl;
        return;
    }

    saveStation(file, station);
    file.close();

    if (!file)
    {
        cout << "File error" << endl;
        return;
    }

    cout << "Station saved" << endl;
}


// чтение и проверка данных трубы
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


// чтение и проверка данных станции
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


// отдельная загрузка трубы
bool loadPipeFromFile(Pipe &pipe)
{
    ifstream file("Pipedata.txt");

    if (!file)
    {
        cout << "File not found" << endl;
        return false;
    }

    if (!readPipe(file, pipe))
    {
        cout << "Invalid pipe data" << endl;
        return false;
    }

    cout << "Pipe loaded" << endl;
    return true;
}


// отдельная загрузка станции
bool loadStationFromFile(CompressorStation &station)
{
    ifstream file("Stationdata.txt");

    if (!file)
    {
        cout << "File not found" << endl;
        return false;
    }

    if (!readStation(file, station))
    {
        cout << "Invalid station data" << endl;
        return false;
    }

    cout << "Station loaded" << endl;
    return true;
}


// выбор объектов для сохранения или загрузки
int chooseObjects()
{
    int choice;

    cout << "1. Pipe only (Pipedata.txt)" << endl;
    cout << "2. Station only (Stationdata.txt)" << endl;
    cout << "3. Both objects (data.txt)" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";

    while (!(cin >> choice) || choice < 0 || choice > 3)
    {
        cout << "Wrong choice. Enter number from 0 to 3: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return choice;
}


// общее сохранение в один файл
void saveData(const unordered_map<int, Pipe> &pipes,
              const unordered_map<int, CompressorStation> &stations,
              int nextId)
{
    string filename;
    cout << "Enter filename: ";
    getline(cin >> ws, filename);

    ofstream file(filename);

    if (!file)
    {
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
        cout << "File error" << endl;
        return;
    }

    cout << "Data saved" << endl;
}


// загрузка из одного файла
bool loadData(unordered_map<int, Pipe> &pipes,
              unordered_map<int, CompressorStation> &stations,
              int &nextId)
{
    string filename;
    cout << "Enter filename: ";
    getline(cin >> ws, filename);

    ifstream file(filename);

    if (!file)
    {
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
            cout << "Invalid pipe data" << endl;
            return false;
        }

        if (!loadedPipes.emplace(id, pipe).second)
        {
            cout << "Duplicate ID" << endl;
            return false;
        }
    }

    if (!(file >> stationCount) || stationCount < 0)
    {
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
            cout << "Invalid station data" << endl;
            return false;
        }

        if (loadedPipes.find(id) != loadedPipes.end() ||
            !loadedStations.emplace(id, station).second)
        {
            cout << "Duplicate ID" << endl;
            return false;
        }
    }

    pipes.swap(loadedPipes);
    stations.swap(loadedStations);
    nextId = loadedNextId;

    cout << "Data loaded" << endl;
    return true;
}

void findPipesByName(const unordered_map<int, Pipe> &pipes)
{
    string name;
    cout << "Enter pipe name or part of name: ";
    getline(cin >> ws, name);

    bool found = false;

    for (const auto &item : pipes)
    {
        if (item.second.name.find(name) != string::npos)
        {
            cout << "ID: " << item.first << endl;
            printPipe(item.second);
            cout << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No pipes found" << endl;
    }
}

void findPipesByRepair(const unordered_map<int, Pipe> &pipes)
{
    int repair;
    cout << "Find pipes under repair? (1-yes/0-no): ";

    while (!(cin >> repair) || (repair != 0 && repair != 1))
    {
        cout << "Wrong value. Enter 1 or 0: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    bool found = false;

    for (const auto &item : pipes)
    {
        if (item.second.repair == static_cast<bool>(repair))
        {
            cout << "ID: " << item.first << endl;
            printPipe(item.second);
            cout << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No pipes found" << endl;
    }
}

void findStationsByName(
    const unordered_map<int, CompressorStation> &stations)
{
    string name;
    cout << "Enter station name or part of name: ";
    getline(cin >> ws, name);

    bool found = false;

    for (const auto &item : stations)
    {
        if (item.second.name.find(name) != string::npos)
        {
            cout << "ID: " << item.first << endl;
            printCompressorStation(item.second);
            cout << endl;
            found = true;
        }
    }

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
        cout << "Wrong value. Enter a percentage from 0 to 100: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

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
        }
    }

    if (!found)
    {
        cout << "No stations found" << endl;
    }
}

int main()
{
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;

    int nextId = 1;

    int command = -1;

    while (command != 0)
    {
        cout << endl;

        cout << "1. Add pipe" << endl;
        cout << "2. Add compressor stations" << endl;
        cout << "3. View all objects" << endl;
        cout << "4. Edit pipe status" << endl;
        cout << "5. Edit compressor stations" << endl;
        cout << "6. Save" << endl;
        cout << "7. Load" << endl;
        cout << "8. Delete pipe" << endl;
        cout << "9 Delete KS" << endl;
        cout << "10. Find pipes by name" << endl;
        cout << "11. Find pipes by repair status" << endl;
        cout << "12. Find stations by name" << endl;
        cout << "13. Find stations by unused workshops percentage" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter command: ";

        while (!(cin >> command) ||
               command < 0 ||
               command > 13)
        {
            cout << "Wrong command. Enter number from 0 to 13: ";

            cin.clear();
            cin.ignore(10000, '\n');
        }


        switch (command)
        {
            case 1:
            {
                pipes.emplace(nextId, inputPipe());
                cout << "Pipe added. ID: " << nextId << endl;
                nextId++;
                break;
            }


            case 2:
            {
                stations.emplace(nextId, inputStation());
                cout << "Station added. ID: " << nextId << endl;
                nextId++;
                break;
            }


            case 3:
            {
                if (pipes.empty())
                {
                    cout << "No pipes added" << endl;
                }
                else
                {
                    for (const auto &item : pipes)
                    {
                        cout << "ID: " << item.first << endl;
                        printPipe(item.second);
                        cout << endl;
                    }
                }
                if (stations.empty())
                {
                    cout << "No stations added" << endl;
                }
                else
                {
                    for (const auto &item : stations)
                    {
                        cout << "ID: " << item.first << endl;
                        printCompressorStation(item.second);
                        cout << endl;
                    }
                }

                break; 
            }


            case 4:
            {
                int id;
                cout << "Enter pipe ID: ";

                while (!(cin >> id) || id <= 0)
                {
                    cout << "Wrong ID. Enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }

                auto it = pipes.find(id);

                if (it != pipes.end())
                {
                    editPipe(it->second);
                    cout << "Pipe repair status changed" << endl;
                }
                else
                {
                    cout << "Pipe not found" << endl;
                }

                break;
            }


            case 5:
            {
                int id;
                cout << "Enter stations ID: ";

                while (!(cin >> id) || id <= 0)
                {
                    cout << "Wrong ID. Enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }

                auto it = stations.find(id);

                if (it != stations.end())
                {
                    editStation(it->second);
                }
                else
                {
                    cout << "Station not found" << endl;
                }

                break;
            }


            case 6:
            {
                saveData(pipes, stations, nextId);
                break;
            }


            case 7:
            {
                loadData(pipes, stations, nextId);
                break;
            }

            case 8:
            {
                int id;
                cout << "Enter pipe ID: ";

                while (!(cin >> id) || id <= 0)
                {
                    cout << "Wrong ID. Enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }

                if (pipes.erase(id))
                {
                    cout << "Pipe deleted" << endl;
                }
                else
                {
                    cout << "Pipe not found" << endl;
                }

                break;
            }

            case 9:
            {
                int id;
                cout << "Enter station ID: ";

                while (!(cin >> id) || id <= 0)
                {
                    cout << "Wrong ID. Enter a positive integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                if (stations.erase(id))
                {
                    cout << "Station deleted" << endl;
                }
                else 
                {
                    cout << "Statiom not found" << endl;
                }

                break;
            }

            case 10:
            {
                findPipesByName(pipes);
                break;
            }

            case 11:
            {
                findPipesByRepair(pipes);
                break;
            }

            case 12:
            {
                findStationsByName(stations);
                break;
            }

            case 13:
            {
                findStationsByUnusedPercent(stations);
                break;
            }

            case 0:
                cout << "Exit" << endl;
                break;


            default:
                cout << "Wrong command" << endl;
                break;
        }
    }

    return 0;
}
