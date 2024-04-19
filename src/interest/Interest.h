#ifndef FIN_CALCULATOR_INTEREST_H
#define FIN_CALCULATOR_INTEREST_H

#include "../types/PayInterval.h"
#include "InterestItem.h"
#include "InterestMap.h"

class Interest
{
public:
    Interest(double startCapital, double monthlySavings, unsigned int years, double interestRate, PayInterval payInterval);
    ~Interest();
    [[nodiscard]] double getStartCapital() const;
    [[nodiscard]] double getMonthlySaving() const;
    [[nodiscard]] unsigned int getYears() const;
    [[nodiscard]] double getInterestRate() const;
    [[nodiscard]] PayInterval getPayInterval();
    void changeStartCapital(double capital);
    void changeMonthlySaving(double saving);
    void changeYears(unsigned int savingYears);
    void changeInterestRate(double rate);
    void changePayInterval(PayInterval interval);
    InterestMap calculate();

private:
    double startCapital;
    double monthlySaving;
    unsigned int years;
    double interestRate;
    PayInterval payInterval;
    bool didValuesChange;
    InterestMap data;
    InterestItem calculateForOneYear(InterestItem previousItem);
    [[nodiscard]] double calculateOneUnit(double currentCapital) const;
};

#endif // FIN_CALCULATOR_INTEREST_H