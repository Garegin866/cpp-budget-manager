#pragma once

#include "date.h"

#include <unordered_map>

class BudgetManager {
public:
    static const Date START_DATE;
    static const Date END_DATE;

    void Earn(const Date& from, const Date& to, double value);
    void PayTax(const Date& from, const Date& to);
    [[nodiscard]] double ComputeIncome(const Date& from, const Date& to) const;

private:
    std::unordered_map<int, double> income_;
};