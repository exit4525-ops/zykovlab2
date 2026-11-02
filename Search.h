#pragma once

#include "Pipe.h"
#include "CompressorStation.h"
#include <unordered_map>

void findPipesByName(const std::unordered_map<int, Pipe> &pipes);
void findPipesByRepair(const std::unordered_map<int, Pipe> &pipes);
void findStationsByName(
    const std::unordered_map<int, CompressorStation> &stations);
void findStationsByUnusedPercent(
    const std::unordered_map<int, CompressorStation> &stations);
