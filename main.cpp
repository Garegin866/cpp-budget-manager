#include "budget_manager.h"

#include <iostream>
#include <string_view>

#include "parser.h"

void ParseAndProcessQuery(BudgetManager& manager, std::string_view line) {
    using namespace parser;

    const ParsedQuery query = parser::ParseQueryLine(line);
    switch (query.cmd) {
        case Command::Earn:
            manager.Earn(query.from, query.to, *query.amount);
            break;
        case Command::Spend:
            manager.Spend(query.from, query.to, *query.amount);
            break;
        case Command::PayTax:
            manager.PayTax(query.from, query.to, *query.rate);
            break;
        case Command::ComputeIncome:
            std::cout << manager.ComputeIncome(query.from, query.to) << '\n';
            break;
    }
}

int ReadNumberOnLine(std::istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

int main() {
    BudgetManager manager;

    const int query_count = ReadNumberOnLine(std::cin);

    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(std::cin, line);
        ParseAndProcessQuery(manager, line);
    }
}