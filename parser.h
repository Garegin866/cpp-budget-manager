#pragma once

#include "date.h"

namespace parser {
    enum class Command { Earn, PayTax, Spend, ComputeIncome };

    struct ParsedQuery {
        Command cmd;
        Date from;
        Date to;
        std::optional<double> amount; // Earn/Spend
        std::optional<int> rate;      // PayTax
    };

    ParsedQuery ParseQueryLine(std::string_view line);

} // namespace parser