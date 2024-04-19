#ifndef FIN_CALCULATOR_COMMUTERBENEFITCALCULATOR_H
#define FIN_CALCULATOR_COMMUTERBENEFITCALCULATOR_H

class CommuterBenefitCalculator
{
public:
    CommuterBenefitCalculator(unsigned int workingDays, unsigned int commuteInKm);
    ~CommuterBenefitCalculator();
    [[nodiscard]] unsigned int getWorkingDays() const;
    [[nodiscard]] unsigned int getCommuteInKM() const;
    void changeWorkingDays(unsigned int days);
    void changeCommuteInKM(unsigned int km);
    double calculateBenefit();

private:
    unsigned int workingDays;
    unsigned int commuteInKm;
    const double COMMUTER_BENEFIT_BASIC = 0.3;
    const double COMMUTER_BENEFIT_ADVANCED = 0.38;
    bool didValuesChange;
    double benefitValue;
};

#endif // FIN_CALCULATOR_COMMUTERBENEFITCALCULATOR_H