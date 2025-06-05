#include "utils/Logger.hpp"
#include <iostream>

namespace flashnotes {

Logger::Level Logger::current = Logger::Level::INFO;

namespace {
const char* toString(Logger::Level lvl) {
    switch (lvl) {
    case Logger::Level::DEBUG: return "DEBUG";
    case Logger::Level::INFO:  return "INFO";
    case Logger::Level::WARN:  return "WARN";
    case Logger::Level::ERROR: return "ERROR";
    }
    return "";
}
} // unnamed

void Logger::setLevel(Level lvl) { current = lvl; }

void Logger::log(Level lvl, const std::string& msg) {
    if (lvl < current) return;
    std::clog << '[' << toString(lvl) << "] " << msg << std::endl;
}

void Logger::debug(const std::string& m) { log(Level::DEBUG, m); }
void Logger::info(const std::string& m)  { log(Level::INFO, m); }
void Logger::warn(const std::string& m)  { log(Level::WARN, m); }
void Logger::error(const std::string& m) { log(Level::ERROR, m); }

} // namespace flashnotes
