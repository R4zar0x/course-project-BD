#include "Menu.h"

int Menu::listing()
{
    while (true)
    {
        int k1, k2;
        k1 = _getch();

        if (k1 == 0xE0 || k1 == 0x00)
        {
            k2 = _getch();

            switch (k2)
            {
            case 0x48: return 0x81; break;
            case 0x50: return 0x01; break;
                //case : &this->menu[this->cursor].pointer; break;
            }
        }
        if (k1 == 0xD) return 0xD;
    }
}

void Menu::handler()
{
    unsigned int listenerResponce = this->listing();

    switch (listenerResponce)
    {
    case 0x81:
        if (this->_cursor - 1 >= 0)
            this->_cursor -= 1;
            system("cls");
            this->show();
        break;
    case 0x01:
        if (this->_cursor + 1 < this->_menu.size())
            this->_cursor += 1;
            system("cls");
            this->show();
        break;
    case 0xD:
        system("cls");
        this->_menu[this->_cursor].pointer();
        break;
    }
    
    //system("cls");
    //this->show();
}

Menu::Menu() { }
Menu::Menu(std::vector<menucell>& vec, std::string inscription)
{
    this->_topInscription = inscription;
    for (int cell = 0; cell < vec.size(); cell++)
        _menu.emplace_back(vec[cell]);

    this->_maxsize = this->_menu[0].name.length();

    for (int cell = 0; cell < this->_menu.size(); cell++)
        if (this->_menu[cell].name.length() > _maxsize)
            this->_maxsize = this->_menu[cell].name.length();
}

void Menu::show()
{
    std::string item = "";

    if (!this->_topInscription.empty())
        printf("%s\n", this->_topInscription.data());

    for (int cell = 0; cell < this->_menu.size(); cell++)
    {
        if (cell == this->_cursor)
            printf("> %s\n", this->_menu[cell].name.data());
        else
            printf("- %s\n", this->_menu[cell].name.data());
    }
    this->handler();
}

void Menu::settopin(std::string newTopInscription)
{
    this->_topInscription = newTopInscription;
}

std::string Menu::gettopin()
{
    return this->_topInscription;
}