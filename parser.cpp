#include "parser.h"

#include <iostream>

namespace parser {

    static std::vector<std::string_view> SplitWs(std::string_view s) {
        std::vector<std::string_view> out;
        size_t i = 0, n = s.size();
        while (i < n) {
            while (i < n && s[i] == ' ') ++i;
            if (i >= n) break;
            size_t j = i;
            while (j < n && s[j] != ' ') ++j;
            out.emplace_back(s.data() + i, j - i);
            i = j;
        }
        return out;
    }

    static Command ParseCommand(std::string_view token) {
        if (token == "Earn")           return Command::Earn;
        if (token == "PayTax")         return Command::PayTax;
        if (token == "Spend")          return Command::Spend;
        if (token == "ComputeIncome")  return Command::ComputeIncome;
        throw std::invalid_argument("Unknown command: " + std::string(token));
    }

    static double ParseDoubleSV(std::string_view sv) {
        return std::stod(std::string(sv));
    }

    static int ParseRateSV(std::string_view sv) {
        int r = std::stoi(std::string(sv));
        if (r < 0 || r > 100) {
            throw std::invalid_argument("Tax rate must be 0..100: " + std::string(sv));
        }
        return r;
    }

    ParsedQuery ParseQueryLine(std::string_view line) {
        const auto t = SplitWs(line);
        if (t.size() < 3) {
            throw std::invalid_argument("Not enough tokens in query: " + std::string(line));
        }

        const Command cmd = ParseCommand(t[0]);
        ParsedQuery q{ cmd, Date{t[1]}, Date{t[2]}, std::nullopt, std::nullopt };

        switch (cmd) {
            case Command::Earn:
            case Command::Spend:
                if (t.size() != 4) {
                    throw std::invalid_argument("Earn/Spend expect 4 tokens");
                }
                q.amount = ParseDoubleSV(t[3]);
                break;

            case Command::PayTax:
                if (t.size() != 4) {
                    throw std::invalid_argument("PayTax expects 4 tokens (rate 0..100)");
                }
                q.rate = ParseRateSV(t[3]);
                break;

            case Command::ComputeIncome:
                if (t.size() != 3) {
                    throw std::invalid_argument("ComputeIncome expects 3 tokens");
                }
                break;
        }

        return q;
    }


} // namespace parser