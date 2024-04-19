#ifndef FIN_CALCULATOR_YIELD_H
#define FIN_CALCULATOR_YIELD_H

#include <chrono>

using namespace std;

using namespace std::chrono;

class Yield
{
public:
    Yield(float startValue, float endValue, int startYear, int endYear);
    Yield(float startValue, float endValue);
    Yield(float startValue, float endValue, int startYear);
    ~Yield();
    [[nodiscard]] float getStartValue() const;
    [[nodiscard]] float getEndValue() const;
    [[nodiscard]] int getStartYear() const;
    [[nodiscard]] int getEndYear() const;
    void changeStartValue(float val);
    void changeEndValue(float val);
    void changeStartYear(int year);
    void changeEndYear(int year);
    void calculate();
    [[nodiscard]] double getYieldOverall() const;
    [[nodiscard]] double getYieldPerAnno() const;

private:
    bool didValuesChange;
    float startValue;
    float endValue;
    int startYear;
    int endYear;
    double yieldDataOverall;
    double yieldDataPerAnno;
    bool areYearsProvided;
    [[nodiscard]] double calculateYield() const;
    [[nodiscard]] static double calculateYieldPerAnno(double overallYield, int startYear, int endYear);
    static int calculateCurrentYear();
};

#endif // FIN_CALCULATOR_YIELD_H