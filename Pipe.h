#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct Pipe
{
    std::string name;
    double length;
    int diameter;
    bool repair;
};

Pipe inputPipe();
void printPipe(Pipe pipe);
void editPipe(Pipe &pipe);
void editPipes(std::unordered_map<int, Pipe>
&pipes, const std::vector<int> &ids);

void deletePipes(std::unordered_map<int, Pipe>
&pipes, const std::vector<int> &ids);

void processFoundPipes(std::unordered_map<int, Pipe>
&pipes, const std::vector<int> &ids);
