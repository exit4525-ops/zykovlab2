#pragma once

#include "Pipe.h"
#include "CompressorStation.h"
#include <unordered_map>
#include <fstream>

void savePipe(std::ofstream &file, const Pipe &pipe);
void saveStation(std::ofstream &file, const CompressorStation &station);
bool readPipe(std::ifstream &file, Pipe &pipe);
bool readStation(std::ifstream &file, CompressorStation &station);
void saveData(const std::unordered_map<int, Pipe> &pipes,
              const std::unordered_map<int, CompressorStation> &stations,
              int nextId);
bool loadData(std::unordered_map<int, Pipe> &pipes,
              std::unordered_map<int, CompressorStation> &stations,
              int &nextId);
