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
