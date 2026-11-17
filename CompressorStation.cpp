#include "Logger.h"
#include "CompressorStation.h"

#include <iostream>

using namespace std;

CompressorStation inputStation()
{
    CompressorStation station;

    cout << "Enter station name: ";
    cin >> station.name;

    cout << "Enter number of workshops: ";

    while (!(cin >> station.workshopCount) ||
           station.workshopCount < 0)
    {
        logAction("Invalid input: Wrong value. Enter number of workshops again: ");
        cout << "Wrong value. Enter number of workshops again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter number of workshops in operation: ";

    while (!(cin >> station.workshopsInOperation) ||
           station.workshopsInOperation < 0 ||
           station.workshopsInOperation > station.workshopCount)
    {
        logAction("Invalid input: Wrong value. Enter number of workshops in operation again: ");
        cout << "Wrong value. Enter number of workshops in operation again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter station class: ";

    while (!(cin >> station.stationClass) ||
           station.stationClass < 0)
    {
        logAction("Invalid input: Wrong value. Enter station class again: ");
        cout << "Wrong value. Enter station class again: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    return station;
}

void printCompressorStation(CompressorStation station)
{
    cout << "--- Compressor Station ---" << endl;
    cout << "Name: " << station.name << endl;
    cout << "Workshops: " << station.workshopCount << endl;
    cout << "Workshops in operation: "
         << station.workshopsInOperation << endl;
    cout << "Station class: " << station.stationClass << endl;
}

void editStation(CompressorStation &station)
{
    int choice;

    cout << "1. Start workshop" << endl;
    cout << "2. Stop workshop" << endl;
    cout << "Enter choice: ";

    while (!(cin >> choice) ||
           (choice != 1 && choice != 2))
    {
        logAction("Invalid input: Wrong number. Input new choice: ");
        cout << "Wrong number. Input new choice: ";

        cin.clear();
        cin.ignore(10000, '\n');
    }

    logAction("Station workshop action: " + to_string(choice));

    if (choice == 1)
    {
        if (station.workshopsInOperation < station.workshopCount)
        {
            station.workshopsInOperation++;
            logAction("Workshop started");
            cout << "Workshop started" << endl;
        }
        else
        {
            logAction("All workshops are already working");
            cout << "All workshops are already working" << endl;
        }
    }
    else
    {
        if (station.workshopsInOperation > 0)
        {
            station.workshopsInOperation--;
            logAction("Workshop stopped");
            cout << "Workshop stopped" << endl;
        }
        else
        {
            logAction("No working workshops");
            cout << "No working workshops" << endl;
        }
    }
}
