#pragma once
#include <vector>
#include <unordered_map>
#include "Pipe.h"
#include "CompressorStation.h"

std::vector<int> findPipesByName(
    const std::unordered_map<int, Pipe> &pipes);
std::vector<int> findPipesByRepair(
    const std::unordered_map<int, Pipe> &pipes);
void findStationsByName(
    const std::unordered_map<int, CompressorStation> &stations);
void findStationsByUnusedPercent(
    const std::unordered_map<int, CompressorStation> &stations);
