#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

const int months_in_year = 12;
const double Percent = 100;
const double Max_loanAmount = 9999999.0;
const double Max_InterestRate = 30.0;
const int Min_Years = 1;
const int Max_loanYears = 99;
const double Max_additionalPayment = 9999999.0;

void CommasFormating(double number, ofstream& outFile) // reference from chatgpt for code syntax
{
    int intPart = int(number);
    double fractionalPart = number - intPart;

    int CountingComma = 0;
    string intPartString;

    // Handle the integer part
    do {
        intPartString = char('0' + intPart % 10) + intPartString;
        intPart /= 10;
        CountingComma++;
        if (CountingComma == 3 && intPart > 0) {
            intPartString = "," + intPartString;
            CountingComma = 0;
        }
    } while (intPart > 0);

    outFile << intPartString; // send the integer part to the file 

    if (fractionalPart == 0)
    {
        outFile << ".00";
    }
    else
    {
        // Handle the fractional part
        outFile << ".";
        int fractionalIntPart = int(fractionalPart * 100);
        outFile << char('0' + (fractionalIntPart / 10) % 10);
        outFile << char('0' + fractionalIntPart % 10);
    }
}

int main()
{
    double loanAmount, annualInterestRate, additionalPrincipal;
    int numberOfYears, numberOfMonths;
    string fileName;

    while (true)
    {
        cout << "Enter Loan amount (0-9999999), for example 300000.90: ";
        cin >> loanAmount;

        if (loanAmount > 0 && loanAmount <= Max_loanAmount)
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter annual interest rate (0-30), for example 4.5 meaning 4.5%: ";
        cin >> annualInterestRate;

        if (annualInterestRate > 0 && annualInterestRate <= Max_InterestRate)
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter no. of years as integer (1-99), for example 30: ";
        cin >> numberOfYears;

        if (numberOfYears >= Min_Years && numberOfYears <= Max_loanYears)
        {
            numberOfMonths = numberOfYears * months_in_year;
            break;
        }
    }

    while (true)
    {
        cout << "Enter additional principal per month (0-9999999), for example 300: ";
        cin >> additionalPrincipal;

        if (additionalPrincipal >= 0 && additionalPrincipal <= Max_additionalPayment)
        {
            break;
        }
    }

    cout << "Send the mortgage amortization table to a file (enter file name): ";
    cin >> fileName;

    ofstream outFile(fileName);

    double monthlyInterestRate = annualInterestRate / months_in_year / Percent;
    double monthlyPayment = (loanAmount * monthlyInterestRate) / (1 - pow(1 + monthlyInterestRate, -numberOfYears * months_in_year));
    double actualPayment = monthlyPayment + additionalPrincipal;

    outFile << "\t\tMORTGAGE AMORTIZATION TABLE" << endl;
    outFile << left << setw(30) << "Amount:" << "$ ";
    CommasFormating(loanAmount, outFile);
    outFile << setw(20) << " " << endl;

    outFile << left << setw(30) << "Interest Rate:" << annualInterestRate << "%" << endl;
    outFile << left << setw(30) << "Term (Years):" << numberOfYears << endl;

    outFile << left << setw(30) << "Monthly Payment:" << "$ ";
    CommasFormating(monthlyPayment, outFile);
    outFile << setw(20) << " " << endl;

    outFile << left << setw(30) << "Additional Principal:" << "$ ";
    CommasFormating(additionalPrincipal, outFile);
    outFile << setw(20) << " " << endl;

    outFile << left << setw(30) << "Actual Payment:" << "$ ";
    CommasFormating(actualPayment, outFile);
    outFile << setw(20) << " " << endl << endl;
    outFile << "\t    Principal";
    outFile << "\t        Interest";
    outFile << "\t     Balance" << endl;

    double balance = loanAmount;

    for (int month = 1; balance > 0; month++)
    {
        double interest = balance * monthlyInterestRate;
        double principal = actualPayment - interest;
        balance -= principal;

        if (balance < 0)
        {
            principal += balance;
            balance = 0;
        }

        if (month == 1)
        {
            outFile << setw(5) << month << " $ ";
            outFile << fixed << setprecision(2) << setw(10) << right;
            CommasFormating(principal, outFile);
            outFile << "  $   ";
            outFile << setw(10) << right;
            CommasFormating(interest, outFile);
            outFile << "  $  " << setw(12) << right;
            CommasFormating(balance, outFile);
            outFile << endl;
        }
        else
        {
            outFile << setw(5) << left << month;
            outFile << fixed << setprecision(2) << setw(13) << right;
            CommasFormating(principal, outFile);
            outFile << setw(16) << right;
            CommasFormating(interest, outFile);
            outFile << setw(17) << right;
            CommasFormating(balance, outFile);
            outFile << endl;
        }
    }

    outFile.close();

    return 0;
}