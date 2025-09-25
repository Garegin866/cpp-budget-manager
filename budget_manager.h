#pragma once
#include "date.h"
#include <vector>

using namespace std::literals;

class BudgetManager {
public:
    BudgetManager();

    void Earn(const Date& from, const Date& to, double amount);
    void Spend(const Date& from, const Date& to, double amount);
    void PayTax(const Date& from, const Date& to, int rate_percent);
    double ComputeIncome(const Date& from, const Date& to) const;

private:
    static const Date epoch_;         // "2000-01-01"
    static const Date end_exclusive_; // "2100-01-01"
    int total_days_ = 0;

    std::vector<double> income_per_day_;
    std::vector<double> expense_per_day_;

    static int DayIndex(const Date& d) { return Date::ComputeDistance(epoch_, d); }
};