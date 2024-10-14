#define _CRT_SECURE_NO_WARNINGS
#define _PRECISSION 2
#define _INDENT 1

#include <stdio.h> // для printf() и scanf()
#include <conio.h> // для _getch()
#include <vector>
#include <string>
#include <fstream>

#include "Menu.h"
#include "myiom.h"

void main_createfile();
void main_openfile();
void main_exit();

void redactor_showtable();
void redactor_savefile();
void redactor_editdata();
void redactor_newdata();
void redactor_exportfile();
void redactor_back();
void redactor_exit();

std::vector<menucell> mMenu =
{
    {"create file", main_createfile},
    {"open file", main_openfile},
    {"exit", main_exit}
};
std::vector<menucell> rMenu =
{
    {"show", redactor_showtable},
    {"save", redactor_savefile},
    {"edit data", redactor_editdata},
    {"add new data", redactor_newdata},
    {"export as table", redactor_exportfile},
    {"back", redactor_back},
    {"exit", redactor_exit}
    };

Menu mainMenu(mMenu, "main menu");
Menu redactorMenu(rMenu, "");

std::string fileName; // = "asd.txt"

std::vector<frow> formatedData;

int row;

int main()
{
    mainMenu.show();

    //redactor_showtable();

    return 0;
}

void main_createfile()
{
    system("cls");
    
    printf("creating new file\n");
    printf("enter new file name: ");

    std::string name;
    scanf("%s", name.data());

    std::ofstream text(name);
    text.close();

    printf("new file created successfully");

    waitkey();
    system("cls");
    mainMenu.show();
}
void main_openfile()
{
    system("cls");

    std::string line;

    printf("opening file\n");
    printf("enter file name: ");
    
    scanf("%s", fileName.data());

    std::ifstream file(fileName);

    redactorMenu.settopin(fileName.data());

    if (file.is_open())
    {
        while (getline(file, line))
        {
            int space = line.find(' ');

            //printf("%s, %d\n", line.substr(0, space).data(), std::stoi(line.substr(space, line.size() - 1)));

            frow dataLine = { line.substr(0, space), std::stoi(line.substr(space, line.size() - 1)) };
            formatedData.push_back(dataLine);
        }
    }
    else
    {
        printf("ERROR");
        exit(0);
    }

    //waitkey();
    system("cls");

    redactorMenu.show();
}
void main_exit()
{
    exit(0);
}

void redactor_showtable()
{
    // заглавие
    std::string titleNumber = "No",
        titleSurname = "Surname",
        titleBid = "Bid",
        titleTax = "Tax",
        titlePensionFund = "Pension",
        titleEmploymentFund = "Employment",
        titleSpent = "Spent",
        titleIssuance = "Issuance"; //loyment

    // максимальный размер
    int maxSizeNumber = std::to_string(formatedData.size()).size(),
        maxSizeSurname = 0,
        maxSizeBid = 0,
        maxSizeTax = 0,
        maxSizePensionFund = 0,
        maxSizeEmploymentFund = 0,
        maxSizeSpent = 0,
        maxSizeIssuance = 0;

    // всего (последняя строка)
    double summTax = 0,
        summPensionFund = 0,
        summEmploymentFund = 0,
        summIssuance = 0;

    //printf("%s\n", std::to_string(2.123).data());

    // поиск самого длинного зачение по размеру
    for (int number = 0; number < formatedData.size(); number++)
    {
        summTax += formatedData[number].tax;
        summPensionFund += formatedData[number].pensionFund;
        summEmploymentFund += formatedData[number].employmentFund;
        summIssuance += formatedData[number].issuance;


        if (formatedData[number].surname.size() > maxSizeSurname)
            maxSizeSurname = formatedData[number].surname.size();

        if (std::to_string(formatedData[number].bid).size() > maxSizeBid)
            maxSizeBid = std::to_string(formatedData[number].bid).size();

        std::string tax = std::to_string(formatedData[number].tax);
        tax.resize(tax.find('.') + _PRECISSION + 1);
        if (tax.size() > maxSizeTax)
            maxSizeTax = tax.size();

        std::string pensionFund = std::to_string(formatedData[number].pensionFund);
        pensionFund.resize(pensionFund.find('.') + _PRECISSION + 1);
        if (pensionFund.size() > maxSizePensionFund)
            maxSizePensionFund = pensionFund.size();

        std::string employmentFund = std::to_string(formatedData[number].employmentFund);
        employmentFund.resize(employmentFund.find('.') + _PRECISSION + 1);
        if (employmentFund.size() > maxSizeEmploymentFund)
            maxSizeEmploymentFund = employmentFund.size();

        std::string spent = std::to_string(formatedData[number].spent);
        spent.resize(spent.find('.') + _PRECISSION + 1);
        if (spent.size() > maxSizeSpent)
            maxSizeSpent = spent.size();

        std::string issuance = std::to_string(formatedData[number].issuance);
        issuance.resize(issuance.find('.') + _PRECISSION + 1);
        if (issuance.size() > maxSizeIssuance)
            maxSizeIssuance = issuance.size();
    }

    // определение что больше занимает значение: в таблице, или в последней строке
    std::string tax = std::to_string(summTax);
    tax.resize(tax.find('.') + _PRECISSION + 1);
    int sizeSummTax = tax.size();
    maxSizeTax = (maxSizeTax > sizeSummTax) ? maxSizeTax : sizeSummTax;

    std::string pensionFund = std::to_string(summPensionFund);
    pensionFund.resize(pensionFund.find('.') + _PRECISSION + 1);
    int sizeSummPensionFund = pensionFund.size();
    maxSizePensionFund = (maxSizePensionFund > sizeSummPensionFund) ? maxSizePensionFund : sizeSummPensionFund;

    std::string employmentFund = std::to_string(summEmploymentFund);
    employmentFund.resize(employmentFund.find('.') + _PRECISSION + 1);
    int sizeSummEmploymentFund = employmentFund.size();
    maxSizeEmploymentFund = (maxSizeEmploymentFund > sizeSummEmploymentFund) ? maxSizeEmploymentFund : sizeSummEmploymentFund;

    std::string issuance = std::to_string(summIssuance);
    issuance.resize(issuance.find('.') + _PRECISSION + 1);
    int sizeSummIssuance = issuance.size();
    maxSizeIssuance = (maxSizeIssuance > sizeSummIssuance) ? maxSizeIssuance : sizeSummIssuance;

    //определение что больше занимает значение: предыдущий вариант, или в заглавии
    maxSizeNumber = (maxSizeNumber > titleNumber.size()) ? maxSizeNumber : titleNumber.size();
    maxSizeSurname = (maxSizeSurname > titleSurname.size()) ? maxSizeSurname : titleSurname.size();
    maxSizeBid = (maxSizeBid > titleBid.size()) ? maxSizeBid : titleBid.size();
    maxSizeTax = (maxSizeTax > titleTax.size()) ? maxSizeTax : titleTax.size();
    maxSizePensionFund = (maxSizePensionFund > titlePensionFund.size()) ? maxSizePensionFund : titlePensionFund.size();
    maxSizeEmploymentFund = (maxSizeEmploymentFund > titleEmploymentFund.size()) ? maxSizeEmploymentFund : titleEmploymentFund.size();
    maxSizeSpent = (maxSizeSpent > titleSpent.size()) ? maxSizeSpent : titleSpent.size();
    maxSizeIssuance = (maxSizeIssuance > titleIssuance.size()) ? maxSizeIssuance : titleIssuance.size();

    /*printf("|%d|%d|%d|%d|%d|%d|%d|%d|\n",
        maxSizeNumber,
        maxSizeSurname,
        maxSizeBid,
        maxSizeTax,
        maxSizePensionFund,
        maxSizeEmploymentFund,
        maxSizeSpent,
        maxSizeIssuance);*/

    std::string gorLine = "|%s|%s|%s|%s|%s|%s|%s|%s|\n";

    std::string startLine =
        "|%" + std::to_string(maxSizeNumber + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeSurname + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeBid + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeTax + _INDENT) + "s|" +
        "%" + std::to_string(maxSizePensionFund + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeEmploymentFund + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeSpent + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeIssuance + _INDENT) + "s|\n";

    printf(gorLine.data(),
        mullstrings("-", maxSizeNumber + _INDENT).data(),
        mullstrings("-", maxSizeSurname + _INDENT).data(),
        mullstrings("-", maxSizeBid + _INDENT).data(),
        mullstrings("-", maxSizeTax + _INDENT).data(),
        mullstrings("-", maxSizePensionFund + _INDENT).data(),
        mullstrings("-", maxSizeEmploymentFund + _INDENT).data(),
        mullstrings("-", maxSizeSpent + _INDENT).data(),
        mullstrings("-", maxSizeIssuance + _INDENT).data());

    printf(startLine.data(), 
        titleNumber.data(),
        titleSurname.data(),
        titleBid.data(),
        titleTax.data(),
        titlePensionFund.data(),
        titleEmploymentFund.data(),
        titleSpent.data(),
        titleIssuance.data());

    printf(gorLine.data(), 
        mullstrings("-", maxSizeNumber + _INDENT).data(),
        mullstrings("-", maxSizeSurname + _INDENT).data(),
        mullstrings("-", maxSizeBid + _INDENT).data(),
        mullstrings("-", maxSizeTax + _INDENT).data(),
        mullstrings("-", maxSizePensionFund + _INDENT).data(),
        mullstrings("-", maxSizeEmploymentFund + _INDENT).data(),
        mullstrings("-", maxSizeSpent + _INDENT).data(),
        mullstrings("-", maxSizeIssuance + _INDENT).data());

    for (int number = 0; number < formatedData.size(); number++)
    {
        std::string line =
            "|%" + std::to_string(maxSizeNumber + _INDENT) + "d|" +
            "%" + std::to_string(maxSizeSurname + _INDENT) + "s|" +
            "%" + std::to_string(maxSizeBid + _INDENT) + "d|" +
            "%" + std::to_string(maxSizeTax + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizePensionFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizeEmploymentFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizeSpent + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizeIssuance + _INDENT) + "." + std::to_string(_PRECISSION) + "f|\n";

        printf(line.data(),
            number + 1,
            formatedData[number].surname.data(),
            formatedData[number].bid,
            formatedData[number].tax,
            formatedData[number].pensionFund,
            formatedData[number].employmentFund,
            formatedData[number].spent,
            formatedData[number].issuance
        );
    }

    printf(gorLine.data(),
        mullstrings("-", maxSizeNumber + _INDENT).data(),
        mullstrings("-", maxSizeSurname + _INDENT).data(),
        mullstrings("-", maxSizeBid + _INDENT).data(),
        mullstrings("-", maxSizeTax + _INDENT).data(),
        mullstrings("-", maxSizePensionFund + _INDENT).data(),
        mullstrings("-", maxSizeEmploymentFund + _INDENT).data(),
        mullstrings("-", maxSizeSpent + _INDENT).data(),
        mullstrings("-", maxSizeIssuance + _INDENT).data());

    std::string endLine =
        "|%" + std::to_string(maxSizeNumber + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeSurname + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeBid + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeTax + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
        "%" + std::to_string(maxSizePensionFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
        "%" + std::to_string(maxSizeEmploymentFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
        "%" + std::to_string(maxSizeSpent + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeIssuance + _INDENT) + "." + std::to_string(_PRECISSION) + "f|\n";

    printf(endLine.data(), "", "SUMM", "", summTax, summPensionFund, summEmploymentFund, "", summIssuance);

    waitkey();
    system("cls");
    redactorMenu.show();
}
void redactor_savefile()
{
    FILE* out;
    //std::ofstream out(fileName);
    
    out = fopen(fileName.data(), "w");

    for (int index = 0; index < formatedData.size(); index++)
    {
        fprintf(out, "%s %d\n", formatedData[index].surname.data(), formatedData[index].bid);
        //out << formatedData[index].surname.data() << " " << formatedData[index].bid << "\n";
    }
    //out.close();
    
    fclose(out);

    std::string title = redactorMenu.gettopin();
    if (title.find('*') != -1)
        title.pop_back();
    redactorMenu.settopin(title);

    printf("saved as %s successfully\n", fileName.data());
    waitkey();

    system("cls");
    redactorMenu.show();
}
void redactor_editdata()
{
    std::string newSurname;
    int newBid;

    printf("enter row: ");
    scanf("%d", &row);

    row--;

    printf("press ENTER to leave the value\n");

    printf("[%s] new surname: ", formatedData[row].surname.data());
    if (skip())
    {
        newSurname = formatedData[row].surname;
        printf("\n");
    }
    else
    {
        scanf("%s", newSurname.data());
    }

    printf("[%d] new bid: ", formatedData[row].bid);
    if (skip())
    {
        newBid = formatedData[row].bid;
        printf("\n");
    }
    else
    {
        scanf("%d", &newBid);
    }

    formatedData[row] = { newSurname, newBid };

    std::string title = redactorMenu.gettopin();
    if (title.find('*') == -1)
        title.push_back('*');
    redactorMenu.settopin(title);

    //waitkey();
    system("cls");
    redactorMenu.show();
}
void redactor_newdata()
{
    std::string newSurname;
    int newBid;
    printf("enter syrname: ");
    scanf("%s", newSurname.data());

    printf("enter bid: ");
    scanf_s("%d", &newBid);

    frow dataLine = { newSurname, newBid };
    
    formatedData.push_back(dataLine);

    std::string title = redactorMenu.gettopin();
    if (title.find('*') == -1)
        title.push_back('*');
    redactorMenu.settopin(title);

    system("cls");
    redactorMenu.show();
}
void redactor_exportfile()
{
    std::string name = "_table.txt";
    ///std::ofstream out("table_" + fileName);

    FILE* file;
    
    file = fopen(name.data(), "w");

    //fprintf(file, "%s%d%.2f\n", formatedData[0].surname.data(), formatedData[0].bid, formatedData[0].tax);

    // заглавие
    std::string titleNumber = "No",
        titleSurname = "Surname",
        titleBid = "Bid",
        titleTax = "Tax",
        titlePensionFund = "Pension",
        titleEmploymentFund = "Employment",
        titleSpent = "Spent",
        titleIssuance = "Issuance"; 

    // максимальный размер
    int maxSizeNumber = std::to_string(formatedData.size()).size(),
        maxSizeSurname = 0,
        maxSizeBid = 0,
        maxSizeTax = 0,
        maxSizePensionFund = 0,
        maxSizeEmploymentFund = 0,
        maxSizeSpent = 0,
        maxSizeIssuance = 0;

    // всего (последняя строка)
    double summTax = 0,
        summPensionFund = 0,
        summEmploymentFund = 0,
        summIssuance = 0;

    //printf("%s\n", std::to_string(2.123).data());

    // поиск самого длинного зачение по размеру
    for (int number = 0; number < formatedData.size(); number++)
    {
        summTax += formatedData[number].tax;
        summPensionFund += formatedData[number].pensionFund;
        summEmploymentFund += formatedData[number].employmentFund;
        summIssuance += formatedData[number].issuance;


        if (formatedData[number].surname.size() > maxSizeSurname)
            maxSizeSurname = formatedData[number].surname.size();

        if (std::to_string(formatedData[number].bid).size() > maxSizeBid)
            maxSizeBid = std::to_string(formatedData[number].bid).size();

        std::string tax = std::to_string(formatedData[number].tax);
        tax.resize(tax.find('.') + _PRECISSION + 1);
        if (tax.size() > maxSizeTax)
            maxSizeTax = tax.size();

        std::string pensionFund = std::to_string(formatedData[number].pensionFund);
        pensionFund.resize(pensionFund.find('.') + _PRECISSION + 1);
        if (pensionFund.size() > maxSizePensionFund)
            maxSizePensionFund = pensionFund.size();

        std::string employmentFund = std::to_string(formatedData[number].employmentFund);
        employmentFund.resize(employmentFund.find('.') + _PRECISSION + 1);
        if (employmentFund.size() > maxSizeEmploymentFund)
            maxSizeEmploymentFund = employmentFund.size();

        std::string spent = std::to_string(formatedData[number].spent);
        spent.resize(spent.find('.') + _PRECISSION + 1);
        if (spent.size() > maxSizeSpent)
            maxSizeSpent = spent.size();

        std::string issuance = std::to_string(formatedData[number].issuance);
        issuance.resize(issuance.find('.') + _PRECISSION + 1);
        if (issuance.size() > maxSizeIssuance)
            maxSizeIssuance = issuance.size();
    }

    // определение что больше занимает значение: в таблице, или в последней строке
    std::string tax = std::to_string(summTax);
    tax.resize(tax.find('.') + _PRECISSION + 1);
    int sizeSummTax = tax.size();
    maxSizeTax = (maxSizeTax > sizeSummTax) ? maxSizeTax : sizeSummTax;

    std::string pensionFund = std::to_string(summPensionFund);
    pensionFund.resize(pensionFund.find('.') + _PRECISSION + 1);
    int sizeSummPensionFund = pensionFund.size();
    maxSizePensionFund = (maxSizePensionFund > sizeSummPensionFund) ? maxSizePensionFund : sizeSummPensionFund;

    std::string employmentFund = std::to_string(summEmploymentFund);
    employmentFund.resize(employmentFund.find('.') + _PRECISSION + 1);
    int sizeSummEmploymentFund = employmentFund.size();
    maxSizeEmploymentFund = (maxSizeEmploymentFund > sizeSummEmploymentFund) ? maxSizeEmploymentFund : sizeSummEmploymentFund;

    std::string issuance = std::to_string(summIssuance);
    issuance.resize(issuance.find('.') + _PRECISSION + 1);
    int sizeSummIssuance = issuance.size();
    maxSizeIssuance = (maxSizeIssuance > sizeSummIssuance) ? maxSizeIssuance : sizeSummIssuance;

    //определение что больше занимает значение: предыдущий вариант, или в заглавии
    maxSizeNumber = (maxSizeNumber > titleNumber.size()) ? maxSizeNumber : titleNumber.size();
    maxSizeSurname = (maxSizeSurname > titleSurname.size()) ? maxSizeSurname : titleSurname.size();
    maxSizeBid = (maxSizeBid > titleBid.size()) ? maxSizeBid : titleBid.size();
    maxSizeTax = (maxSizeTax > titleTax.size()) ? maxSizeTax : titleTax.size();
    maxSizePensionFund = (maxSizePensionFund > titlePensionFund.size()) ? maxSizePensionFund : titlePensionFund.size();
    maxSizeEmploymentFund = (maxSizeEmploymentFund > titleEmploymentFund.size()) ? maxSizeEmploymentFund : titleEmploymentFund.size();
    maxSizeSpent = (maxSizeSpent > titleSpent.size()) ? maxSizeSpent : titleSpent.size();
    maxSizeIssuance = (maxSizeIssuance > titleIssuance.size()) ? maxSizeIssuance : titleIssuance.size();

    /*printf("|%d|%d|%d|%d|%d|%d|%d|%d|\n",
        maxSizeNumber,
        maxSizeSurname,
        maxSizeBid,
        maxSizeTax,
        maxSizePensionFund,
        maxSizeEmploymentFund,
        maxSizeSpent,
        maxSizeIssuance);*/

    // горизонтальные строки
    std::string gorLine = "|%s|%s|%s|%s|%s|%s|%s|%s|\n";

    // заглавие
    std::string startLine =
        "|%" + std::to_string(maxSizeNumber + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeSurname + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeBid + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeTax + _INDENT) + "s|" +
        "%" + std::to_string(maxSizePensionFund + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeEmploymentFund + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeSpent + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeIssuance + _INDENT) + "s|\n";

    fprintf(file, gorLine.data(),
        mullstrings("-", maxSizeNumber + _INDENT).data(),
        mullstrings("-", maxSizeSurname + _INDENT).data(),
        mullstrings("-", maxSizeBid + _INDENT).data(),
        mullstrings("-", maxSizeTax + _INDENT).data(),
        mullstrings("-", maxSizePensionFund + _INDENT).data(),
        mullstrings("-", maxSizeEmploymentFund + _INDENT).data(),
        mullstrings("-", maxSizeSpent + _INDENT).data(),
        mullstrings("-", maxSizeIssuance + _INDENT).data());

    fprintf(file, startLine.data(),
        titleNumber.data(),
        titleSurname.data(),
        titleBid.data(),
        titleTax.data(),
        titlePensionFund.data(),
        titleEmploymentFund.data(),
        titleSpent.data(),
        titleIssuance.data());

    fprintf(file, gorLine.data(),
        mullstrings("-", maxSizeNumber + _INDENT).data(),
        mullstrings("-", maxSizeSurname + _INDENT).data(),
        mullstrings("-", maxSizeBid + _INDENT).data(),
        mullstrings("-", maxSizeTax + _INDENT).data(),
        mullstrings("-", maxSizePensionFund + _INDENT).data(),
        mullstrings("-", maxSizeEmploymentFund + _INDENT).data(),
        mullstrings("-", maxSizeSpent + _INDENT).data(),
        mullstrings("-", maxSizeIssuance + _INDENT).data());

    for (int number = 0; number < formatedData.size(); number++)
    {
        std::string line =
            "|%" + std::to_string(maxSizeNumber + _INDENT) + "d|" +
            "%" + std::to_string(maxSizeSurname + _INDENT) + "s|" +
            "%" + std::to_string(maxSizeBid + _INDENT) + "d|" +
            "%" + std::to_string(maxSizeTax + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizePensionFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizeEmploymentFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizeSpent + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
            "%" + std::to_string(maxSizeIssuance + _INDENT) + "." + std::to_string(_PRECISSION) + "f|\n";

        fprintf(file, line.data(),
            number + 1,
            formatedData[number].surname.data(),
            formatedData[number].bid,
            formatedData[number].tax,
            formatedData[number].pensionFund,
            formatedData[number].employmentFund,
            formatedData[number].spent,
            formatedData[number].issuance
        );
    }

    fprintf(file, gorLine.data(),
        mullstrings("-", maxSizeNumber + _INDENT).data(),
        mullstrings("-", maxSizeSurname + _INDENT).data(),
        mullstrings("-", maxSizeBid + _INDENT).data(),
        mullstrings("-", maxSizeTax + _INDENT).data(),
        mullstrings("-", maxSizePensionFund + _INDENT).data(),
        mullstrings("-", maxSizeEmploymentFund + _INDENT).data(),
        mullstrings("-", maxSizeSpent + _INDENT).data(),
        mullstrings("-", maxSizeIssuance + _INDENT).data());

    // итоги
    std::string endLine =
        "|%" + std::to_string(maxSizeNumber + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeSurname + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeBid + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeTax + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
        "%" + std::to_string(maxSizePensionFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
        "%" + std::to_string(maxSizeEmploymentFund + _INDENT) + "." + std::to_string(_PRECISSION) + "f|" +
        "%" + std::to_string(maxSizeSpent + _INDENT) + "s|" +
        "%" + std::to_string(maxSizeIssuance + _INDENT) + "." + std::to_string(_PRECISSION) + "f|\n";

    fprintf(file, endLine.data(), "", "SUMM", "", summTax, summPensionFund, summEmploymentFund, "", summIssuance);


    fclose(file);

    printf("exported successfully\n");
    waitkey();

    system("cls");
    redactorMenu.show();
}
void redactor_back()
{
    formatedData.clear();

    mainMenu.show();
}
void redactor_exit()
{
    exit(0);
}
