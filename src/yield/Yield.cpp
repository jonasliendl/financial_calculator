#include "Yield.h"
#include <cmath>

Yield::Yield(float startValue, float endValue, int startYear, int endYear)
{
    this->didValuesChange = true;
    this->startYear = startYear;
    this->endYear = endYear;
    this->startValue = startValue;
    this->endValue = endValue;
    this->yieldDataOverall = 0.0;
    this->yieldDataPerAnno = 0.0;
    this->areYearsProvided = true;
}

float Yield::getStartValue() const
{
    return this->startValue;
}

float Yield::getEndValue() const
{
    return this->endValue;
}

int Yield::getStartYear() const
{
    return this->startYear;
}

int Yield::getEndYear() const
{
    return this->endYear;
}

void Yield::changeStartValue(float val)
{
    this->startValue = val;
    this->didValuesChange = true;
}

void Yield::changeEndValue(float val)
{
    this->endValue = val;
    this->didValuesChange = true;
}

void Yield::changeStartYear(int year)
{
    this->startYear = year;
    this->didValuesChange = true;
}

void Yield::changeEndYear(int year)
{
    this->endYear = year;
    this->didValuesChange = true;
}

void Yield::calculate()
{
    if (this->didValuesChange)
    {
        if (this->endValue == 0.0)
        {
            this->didValuesChange = false;
            this->yieldDataOverall = -1.0;
            this->yieldDataPerAnno = -1.0;
            return;
        }

        if (this->startValue == 0.0)
        {
            this->didValuesChange = false;
            this->yieldDataOverall = NAN;
            this->yieldDataPerAnno = NAN;
            return;
        }

        double yield = this->calculateYield();
        this->yieldDataPerAnno = Yield::calculateYieldPerAnno(yield, this->startYear, this->endYear);
        this->yieldDataOverall = yield;
        this->didValuesChange = false;
        return;
    }
}

Yield::Yield(float startValue, float endValue)
{
    didValuesChange = true;
    areYearsProvided = false;

    this->startValue = startValue;
    this->endValue = endValue;

    int currentYear = Yield::calculateCurrentYear();
    startYear = currentYear;
    endYear = currentYear;

    yieldDataOverall = 0.0;
    yieldDataPerAnno = 0.0;
}

Yield::Yield(float startValue, float endValue, int startYear)
{
    didValuesChange = true;
    areYearsProvided = true;

    this->startValue = startValue;
    this->endValue = endValue;
    this->startYear = startYear;

    endYear = Yield::calculateCurrentYear();
    yieldDataOverall = 0.0;
    yieldDataPerAnno = 0.0;
}

double Yield::getYieldOverall() const
{
    return this->yieldDataOverall;
}

double Yield::getYieldPerAnno() const
{
    return this->yieldDataPerAnno;
}

double Yield::calculateYield() const
{
    return this->endValue / this->startValue - 1.0;
}

double Yield::calculateYieldPerAnno(double yieldOverall, int startYear, int endYear)
{
    if (startYear == endYear)
    {
        return yieldOverall;
    }
    int passedYears = endYear - startYear;
    double performancePA = pow(1.0 + yieldOverall, 1.0 / passedYears);
    return performancePA - 1.0;
}

int Yield::calculateCurrentYear()
{
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&timeNow);
    return localTime->tm_year + 1900;
}

Yield::~Yield() = default;
