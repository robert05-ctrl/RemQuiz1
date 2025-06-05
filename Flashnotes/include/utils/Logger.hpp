#pragma once
#include <string>
#include <iostream>

namespace flashnotes {

class Logger {
public:
    enum class Level { DEBUG, INFO, WARN, ERROR };
    static void setLevel(Level);
    static void debug(const std::string&);
    static void info (const std::string&);
    static void warn (const std::string&);
    static void error(const std::string&);
private:
    static Level current;
    static void log(Level, const std::string&);
};

} // namespace flashnotes
