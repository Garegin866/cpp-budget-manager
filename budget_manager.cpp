#include "budget_manager.h"
#include "date.h"

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);

void BudgetManager::Earn(const Date& from, const Date& to, double value) {
    int days = Date::ComputeDistance(from, to) + 1;
    double daily_income = value / days;
    for (int i = 0; i < days; ++i) {
        income_[Date::ComputeDistance(START_DATE, from) + i] += daily_income;
    }
}

void BudgetManager::PayTax(const Date& from, const Date& to) {
    int days = Date::ComputeDistance(from, to) + 1;
    for (int i = 0; i < days; ++i) {
        income_[Date::ComputeDistance(START_DATE, from) + i] *= 0.87;
    }
}

double BudgetManager::ComputeIncome(const Date& from, const Date& to) const {
    double total_income = 0.0;
    int days = Date::ComputeDistance(from, to) + 1;
    for (int i = 0; i < days; ++i) {
        auto it = income_.find(Date::ComputeDistance(START_DATE, from) + i);
        if (it != income_.end()) {
            total_income += it->second;
        }
    }
    return total_income;
}