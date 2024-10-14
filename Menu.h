#pragma once
#include <string>
#include <vector>
#include <conio.h>

struct menucell
{
	std::string name;
	void(*pointer)();
};

class Menu
{
protected:
    std::vector<menucell> _menu;
    std::string _topInscription = "";
    int _maxsize;
    int _cursor = 0;

    int listing();

    void handler();

public:
    Menu();
    Menu(std::vector<menucell>&, std::string);

    void show();

    void settopin(std::string);
    
    std::string gettopin();

};

