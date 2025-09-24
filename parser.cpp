#include "parser.h"

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
        if (token == "ComputeIncome")  return Command::ComputeIncome;
        throw std::invalid_argument("Unknown command: " + std::string(token));
    }

    static double ParseDoubleSV(std::string_view sv) {
        return std::stod(std::string(sv));
    }

    ParsedQuery ParseQueryLine(std::string_view line) {
        const auto t = SplitWs(line);
        if (t.size() < 3) {
            throw std::invalid_argument("Not enough tokens in query: " + std::string(line));
        }

        ParsedQuery q{ ParseCommand(t[0]), Date{t[1]}, Date{t[2]}, std::nullopt };

        if (q.cmd == Command::Earn) {
            if (t.size() != 4) throw std::invalid_argument("Earn expects 4 tokens");
            q.value = ParseDoubleSV(t[3]);
        } else {
            if (t.size() != 3) throw std::invalid_argument("Command expects 3 tokens");
        }

        return q;
    }


} // namespace parser