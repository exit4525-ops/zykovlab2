#include "Pipe.h"

#include <iostream>

using namespace std;

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

void editPipe(Pipe &pipe)
{
    pipe.repair = !pipe.repair;
}
