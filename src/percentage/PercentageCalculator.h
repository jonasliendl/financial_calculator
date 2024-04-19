#ifndef FIN_CALCULATOR_PERCENTAGECALCULATOR_H
#define FIN_CALCULATOR_PERCENTAGECALCULATOR_H

class PercentageCalculator
{
public:
    PercentageCalculator();
    ~PercentageCalculator();
    [[nodiscard]] double getStartValue() const;
    [[nodiscard]] double getEndValue() const;
    [[nodiscard]] double getInterestRate() const;
    void changeStartValue(double val);
    void changeEndValue(double val);
    void changeInterestRate(double rate);
    double calculateStartValue();
    double calculateEndValue();
    double calculateInterestRate();

private:
    double startValue;
    double endValue;
    double interestRate;
    bool didValuesChange;
};

#endif // FIN_CALCULATOR_PERCENTAGECALCULATOR_H