#include "budget_manager.h"

#include "date.h"
#include <vector>

const Date BudgetManager::epoch_ = Date("2000-01-01"s);
const Date BudgetManager::end_exclusive_ = Date("2100-01-01"s);

BudgetManager::BudgetManager() {
    total_days_ = Date::ComputeDistance(epoch_, end_exclusive_);
    income_per_day_.assign(total_days_, 0.0);
    expense_per_day_.assign(total_days_, 0.0);
}

void BudgetManager::Earn(const Date& from, const Date& to, double amount) {
    const int l = DayIndex(from), r = DayIndex(to);
    const int days = r - l + 1;
    const double per_day = amount / days;
    for (int i = l; i <= r; ++i) income_per_day_[i] += per_day;
}

void BudgetManager::Spend(const Date& from, const Date& to, double amount) {
    const int l = DayIndex(from), r = DayIndex(to);
    const int days = r - l + 1;
    const double per_day = amount / days;
    for (int i = l; i <= r; ++i) expense_per_day_[i] += per_day;
}

void BudgetManager::PayTax(const Date& from, const Date& to, int rate_percent) {
    const int l = DayIndex(from), r = DayIndex(to);
    const double factor = 1.0 - static_cast<double>(rate_percent)/100.0;
    for (int i = l; i <= r; ++i) income_per_day_[i] *= factor; // только доход
}

double BudgetManager::ComputeIncome(const Date& from, const Date& to) const {
    const int l = DayIndex(from), r = DayIndex(to);
    double sum = 0.0;
    for (int i = l; i <= r; ++i) sum += income_per_day_[i] - expense_per_day_[i];
    return sum;
}