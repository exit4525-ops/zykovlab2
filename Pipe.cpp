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

void editPipes(unordered_map<int, Pipe> &pipes,
               const vector<int> &ids)
{
    if (ids.empty())
    {
        return;
    }

    int mode;
    cout << "1. Edit all found pipes" << endl;
    cout << "2. Select pipes individually" << endl;
    cout << "0. Cancel" << endl;

    while (!(cin >> mode) || mode < 0 || mode > 2)
    {
        cout << "Enter 0, 1 or 2: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (mode == 0)
    {
        return;
    }

    int repair;
    cout << "New repair status (1-yes/0-no): ";

    while (!(cin >> repair) || (repair != 0 && repair != 1))
    {
        cout << "Enter 1 or 0: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int changed = 0;

    for (int id : ids)
    {
        auto it = pipes.find(id);

        if (it == pipes.end())
        {
            continue;
        }

        if (mode == 2)
        {
            int selected;
            cout << "Edit pipe ID " << id << "? (1-yes/0-no): ";

            while (!(cin >> selected) ||
                   (selected != 0 && selected != 1))
            {
                cout << "Enter 1 or 0: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            if (selected == 0)
            {
                continue;
            }
        }

        it->second.repair = (repair == 1);
        changed++;
    }

    cout << "Pipes processed: " << changed << endl;
}

void deletePipes(unordered_map<int, Pipe> &pipes,
                 const vector<int> &ids)
{
    if (ids.empty())
    {
        return;
    }

    int mode;
    cout << "1. Delete all found pipes" << endl;
    cout << "2. Select pipes individually" << endl;
    cout << "0. Cancel" << endl;

    while (!(cin >> mode) || mode < 0 || mode > 2)
    {
        cout << "Enter 0, 1 or 2: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (mode == 0)
    {
        return;
    }

    int deleted = 0;

    for (int id : ids)
    {
        if (mode == 2)
        {
            int selected;
            cout << "Delete pipe ID " << id << "? (1-yes/0-no): ";

            while (!(cin >> selected) ||
                   (selected != 0 && selected != 1))
            {
                cout << "Enter 1 or 0: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            if (selected == 0)
            {
                continue;
            }
        }

        deleted += pipes.erase(id);
    }

    cout << "Pipes deleted: " << deleted << endl;
}

void processFoundPipes(unordered_map<int, Pipe> &pipes,
                       const vector<int> &ids)
{
    if (ids.empty())
    {
        return;
    }

    int action;
    cout << "1. Edit found pipes" << endl;
    cout << "2. Delete found pipes" << endl;
    cout << "0. Back" << endl;

    while (!(cin >> action) || action < 0 || action > 2)
    {
        cout << "Enter 0, 1 or 2: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (action == 1)
    {
        editPipes(pipes, ids);
    }
    else if (action == 2)
    {
        deletePipes(pipes, ids);
    }
}