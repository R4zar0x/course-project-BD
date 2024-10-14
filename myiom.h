#pragma once
#include <string>
#include <vector>
#include <conio.h>

extern "C" double* _tax(int, double);
extern "C" double* _pensionFund(int, double);
extern "C" double* _employmentFund(int, double);
extern "C" double* _spent(double, double, double);
extern "C" double* _issuance(int, double);

struct frow
{
    std::string surname;
    int bid;

    double tax = *_tax(bid, 0.2); // bid * 0.2 
    double pensionFund = *_pensionFund(bid, 0.01); // bid * 0.01
    double employmentFund = *_employmentFund(bid, 0.005); // bid * 0.005
    double spent = *_spent(tax, pensionFund, employmentFund); // tax + pensionFund + employmentFund
    double issuance = *_issuance(bid, spent); // bid - spent
};

void waitkey();

std::string mullstrings(std::string line, int count);

bool skip();


