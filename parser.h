#pragma once

#include "date.h"

namespace parser {
    enum class Command { Earn, PayTax, ComputeIncome };

    struct ParsedQuery {
        Command cmd;
        Date from;
        Date to;
        std::optional<double> value;
    };

    ParsedQuery ParseQueryLine(std::string_view line);

} // namespace parser