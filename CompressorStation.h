#pragma once

#include <string>

struct CompressorStation
{
    std::string name;
    int workshopCount;
    int workshopsInOperation;
    int stationClass;
};

CompressorStation inputStation();
void printCompressorStation(CompressorStation station);
void editStation(CompressorStation &station);
