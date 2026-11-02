#pragma once

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
