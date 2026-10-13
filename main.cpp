#include <iostream>
#include <string>
#include <fstream>

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
void saveData(Pipe pipe, CompressorStation station)
{
    ofstream file("data.txt");

    if (!file)
    {
        cout << "File error" << endl;
        return;
    }

    savePipe(file, pipe);
    saveStation(file, station);

    file.close();

    if (!file)
    {
        cout << "File error" << endl;
        return;
    }

    cout << "Data saved" << endl;
}


// загрузка из одного файла
bool loadData(Pipe &pipe, CompressorStation &station)
{
    ifstream file("data.txt");

    if (!file)
    {
        cout << "File not found" << endl;
        return false;
    }

    Pipe loadedPipe;
    CompressorStation loadedStation;

    if (!readPipe(file, loadedPipe) || !readStation(file, loadedStation))
    {
        cout << "Invalid data" << endl;
        return false;
    }

    pipe = loadedPipe;
    station = loadedStation;

    file.close();

    cout << "Data loaded" << endl;

    return true;
}


int main()
{
    Pipe pipe;
    CompressorStation station;

    bool pipeExists = false;
    bool stationExists = false;

    int command = -1;

    while (command != 0)
    {
        cout << endl;

        cout << "1. Add pipe" << endl;
        cout << "2. Add compressor station" << endl;
        cout << "3. View all objects" << endl;
        cout << "4. Edit pipe status" << endl;
        cout << "5. Edit compressor station" << endl;
        cout << "6. Save" << endl;
        cout << "7. Load" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter command: ";

        while (!(cin >> command) ||
               command < 0 ||
               command > 7)
        {
            cout << "Wrong command. Enter number from 0 to 7: ";

            cin.clear();
            cin.ignore(10000, '\n');
        }


        switch (command)
        {
            case 1:
                pipe = inputPipe();
                pipeExists = true;
                break;


            case 2:
                station = inputStation();
                stationExists = true;
                break;


            case 3:
                if (pipeExists)
                {
                    printPipe(pipe);
                }
                else
                {
                    cout << "Pipe not added" << endl;
                }

                cout << endl;

                if (stationExists)
                {
                    printCompressorStation(station);
                }
                else
                {
                    cout << "Station not added" << endl;
                }

                break;


            case 4:
                if (pipeExists)
                {
                    editPipe(pipe);

                    cout << "Pipe repair status changed" << endl;
                }
                else
                {
                    cout << "Pipe not added" << endl;
                }

                break;


            case 5:
                if (stationExists)
                {
                    editStation(station);
                }
                else
                {
                    cout << "Station not added" << endl;
                }

                break;


            case 6:
                {
                    int choice = chooseObjects();

                    if (choice == 1)
                    {
                        if (pipeExists)
                            savePipeToFile(pipe);
                        else
                            cout << "Pipe not added" << endl;
                    }
                    else if (choice == 2)
                    {
                        if (stationExists)
                            saveStationToFile(station);
                        else
                            cout << "Station not added" << endl;
                    }
                    else if (choice == 3)
                    {
                        if (pipeExists && stationExists)
                            saveData(pipe, station);
                        else
                            cout << "Add pipe and station first" << endl;
                    }
                }

                break;


            case 7:
                {
                    int choice = chooseObjects();

                    if (choice == 1)
                    {
                        if (loadPipeFromFile(pipe))
                            pipeExists = true;
                    }
                    else if (choice == 2)
                    {
                        if (loadStationFromFile(station))
                            stationExists = true;
                    }
                    else if (choice == 3)
                    {
                        if (loadData(pipe, station))
                        {
                            pipeExists = true;
                            stationExists = true;
                        }
                    }
                }

                break;


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
