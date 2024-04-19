#include "PercentageCalculator.h"
#include "../exception/Exception.h"

PercentageCalculator::PercentageCalculator()
{
    this->didValuesChange = false;
    this->startValue = 0.0;
    this->endValue = 0.0;
    this->interestRate = 0.0;
}

double PercentageCalculator::getStartValue() const
{
    return this->startValue;
}

double PercentageCalculator::getEndValue() const
{
    return this->endValue;
}

double PercentageCalculator::getInterestRate() const
{
    return this->interestRate;
}

void PercentageCalculator::changeStartValue(double val)
{
    this->didValuesChange = true;
    this->startValue = val;
}

void PercentageCalculator::changeEndValue(double val)
{
    this->didValuesChange = true;
    this->endValue = val;
}

void PercentageCalculator::changeInterestRate(double rate)
{
    this->didValuesChange = true;
    this->interestRate = rate;
}

double PercentageCalculator::calculateStartValue()
{
    if (didValuesChange)
    {
        if (endValue == 0.0)
        {
            throw Exception("Unable to calculate start value from end value equals 0.0");
        }

        double startVal = endValue / ((interestRate + 100) / 100);

        didValuesChange = false;
        startValue = startVal;

        return startVal;
    }
    else
    {
        return this->startValue;
    }
}

double PercentageCalculator::calculateEndValue()
{
    if (didValuesChange)
    {
        if (startValue == 0.0)
        {
            throw Exception("Unable to calculate end value from start value equals 0.0");
        }

        double difference = startValue * (interestRate / 100);
        double endVal = startValue + difference;

        didValuesChange = false;
        endValue = endVal;

        return endVal;
    }
    else
    {
        return endValue;
    }
}

double PercentageCalculator::calculateInterestRate()
{
    if (didValuesChange)
    {
        if (startValue == 0.0)
        {
            throw Exception("Unable to calculate interest rate with start value equals 0.0");
        }

        double rate = 0.0;

        if (startValue != endValue)
        {
            rate = (endValue - startValue) / startValue;
        }

        didValuesChange = false;
        interestRate = rate;

        return rate;
    }
    else
    {
        return endValue;
    }
}

PercentageCalculator::~PercentageCalculator() = default;