#include "Pipe.h"
#include "CompressorStation.h"
#include "Storage.h"
#include "Search.h"
#include "Logger.h"
#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    logAction("Program started");
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
        cout << "9. Delete KS" << endl;
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
            logAction("Invalid menu command");
            cout << "Wrong command. Enter number from 0 to 13: ";

            cin.clear();
            cin.ignore(10000, '\n');
        }

        logAction("Menu command: " + to_string(command));
        switch (command)
        {
            case 1:
            {
                pipes.emplace(nextId, inputPipe());
                logAction("Pipe added. ID: " + to_string(nextId));
                cout << "Pipe added. ID: " << nextId << endl;
                nextId++;
                break;
            }


            case 2:
            {
                stations.emplace(nextId, inputStation());
                logAction("Station added. ID: " + to_string(nextId));
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
                    logAction("Pipe edited. ID: " + to_string(id)
                                + ". Repair: " + to_string(it->second.repair));
                    cout << "Pipe repair status changed" << endl;
                }
                else
                {
                    cout << "Pipe not found" << endl;
                    logAction("Edit failed: pipe not found. ID: " + to_string(id));
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
                    logAction("Station edit completed. ID: " + to_string(id)
                              + ". Working workshops: " + to_string(it->second.workshopsInOperation));
                }
                else
                {
                    cout << "Station not found" << endl;
                    logAction("Edit failed: station not found. ID: " + to_string(id));
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
                    logAction("Pipe deleted. ID: " + to_string(id));
                }
                else
                {
                    cout << "Pipe not found" << endl;
                    logAction("Delete failed: pipe not found. ID: " + to_string(id));
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
                    logAction("Station deleted. ID: " + to_string(id));
                }
                else
                {
                    cout << "Station not found" << endl;
                    logAction("Delete failed: station not found. ID: " + to_string(id));
                }

                break;
            }

            case 10:
            {
                auto ids = findPipesByName(pipes);
                processFoundPipes(pipes, ids);
                break;
            }

            case 11:
            {
                auto ids = findPipesByRepair(pipes);
                processFoundPipes(pipes, ids);
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

    logAction("Program finished");
    return 0;
}
