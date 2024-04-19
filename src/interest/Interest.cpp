#include "Interest.h"
#include <iostream>

Interest::Interest(double startCapital, double monthlySaving, unsigned int years, double interestRate, PayInterval payInterval)
{
    this->startCapital = startCapital;
    this->monthlySaving = monthlySaving;
    this->years = years;
    this->interestRate = interestRate;
    this->payInterval = payInterval;

    didValuesChange = true;
}

double Interest::getStartCapital() const
{
    return startCapital;
}

double Interest::getMonthlySaving() const
{
    return monthlySaving;
}

unsigned int Interest::getYears() const
{
    return years;
}

double Interest::getInterestRate() const
{
    return interestRate;
}

PayInterval Interest::getPayInterval()
{
    return payInterval;
}

void Interest::changeStartCapital(double capital)
{
    startCapital = capital;
    didValuesChange = true;
}

void Interest::changeMonthlySaving(double saving)
{
    monthlySaving = saving;
    didValuesChange = true;
}

void Interest::changeYears(unsigned int savingYears)
{
    years = savingYears;
    didValuesChange = true;
}

void Interest::changeInterestRate(double rate)
{
    interestRate = rate;
    didValuesChange = true;
}

void Interest::changePayInterval(PayInterval interval)
{
    payInterval = interval;
    didValuesChange = true;
}

InterestMap Interest::calculate()
{
    if (didValuesChange)
    {
        InterestMap interestMap{};

        for (int i = 0; i < years; i++)
        {
            InterestItem previousItem{};
            if (i == 0)
            {
                previousItem = {startCapital, 0};
            }
            else
            {
                previousItem = interestMap[i - 1];
            }
            InterestItem item = calculateForOneYear(previousItem);
            interestMap[i] = item;
        }

        data = interestMap;

        return interestMap;
    }
    else
    {
        return data;
    }
}

InterestItem Interest::calculateForOneYear(InterestItem previousItem)
{
    int ITERATIONS = 1;

    double savingPerMonth = monthlySaving;

    switch (payInterval)
    {
    case MONTHLY:
        ITERATIONS = 12;
        break;
    case QUARTERLY:
        ITERATIONS = 4;
        savingPerMonth = monthlySaving / 6;
        break;
    case YEARLY:
        ITERATIONS = 1;
        savingPerMonth = monthlySaving / 12;
        break;
    }

    double currentCapital = previousItem.deposit + previousItem.interestReceived;
    for (int i = 0; i < ITERATIONS; i++)
    {
        currentCapital = calculateOneUnit(currentCapital + savingPerMonth);
    }
    const double gainedCapital = currentCapital - previousItem.deposit - (monthlySaving * 12);
    const double depositCapital = previousItem.deposit + (12 * monthlySaving);
    return {depositCapital, gainedCapital};
}

double Interest::calculateOneUnit(double currentCapital) const
{
    double calculatedVal = (currentCapital * (interestRate / 100)) / 12;
    return calculatedVal + currentCapital;
}

Interest::~Interest() = default;