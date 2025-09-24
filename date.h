#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <string_view>

inline bool parseYmdPortable(std::string_view s, std::chrono::year_month_day& out) {
    using namespace std;
    using namespace std::chrono;

    int y=0, m=0, d=0;
    const char* p = s.data();
    const char* e = p + s.size();

    auto read = [&](int& v)->bool {
        auto r = from_chars(p, e, v);
        if (r.ec != errc{}) return false;
        p = r.ptr;
        return true;
    };

    if (!read(y) || p==e || *p++!='-' || !read(m) || p==e || *p++!='-' || !read(d) || p!=e)
        return false;

    year_month_day ymd{year{y}, month{static_cast<unsigned>(m)}, day{static_cast<unsigned>(d)}};
    if (!ymd.ok()) return false;
    out = ymd;
    return true;
}

class Date {
public:
    explicit Date(const std::string& str) {
        if (!parseYmdPortable(str, ymd_)) {
            throw std::invalid_argument("Invalid date: " + str);
        }
    }

    explicit Date(std::string_view str)
        : Date(std::string(str)) {
    }

    static int ComputeDistance(const Date& from, const Date& to) {
        return static_cast<int>(
            (std::chrono::sys_days(to.ymd_) - std::chrono::sys_days(from.ymd_)).count());
    }

private:
    std::chrono::year_month_day ymd_{};
};