#include "myiom.h"
#include <iostream>


void waitkey()
{
    int key;
    while (true)
    {
        key = _getch();
        if (key == 0xD) break;
    }
}

std::string mullstrings(std::string line, int count)
{
    std::string spaces = "";

    for (int chr = 0; chr < count; chr++) spaces.append(line);

    return spaces;
}

bool skip()
{
    while (true)
    {
        int k = _getch();

        if (k == 0xD) return true;
        else return false;
    }
}
