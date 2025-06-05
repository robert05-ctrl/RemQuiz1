#pragma once
#include <variant>
#include <string>

namespace flashnotes {

template <typename T>
class Expected {
    std::variant<T, std::string> data_;
public:
    Expected(const T& val) : data_(val) {}
    Expected(T&& val) : data_(std::move(val)) {}
    Expected(const std::string& err) : data_(err) {}
    Expected(std::string&& err) : data_(std::move(err)) {}
    bool hasValue() const { return std::holds_alternative<T>(data_); }
    explicit operator bool() const { return hasValue(); }
    T& value() { return std::get<T>(data_); }
    const T& value() const { return std::get<T>(data_); }
    const std::string& error() const { return std::get<std::string>(data_); }
};

template <>
class Expected<void> {
    std::variant<std::monostate, std::string> data_;
public:
    Expected() : data_(std::monostate{}) {}
    Expected(const std::string& err) : data_(err) {}
    Expected(std::string&& err) : data_(std::move(err)) {}
    bool hasValue() const { return std::holds_alternative<std::monostate>(data_); }
    explicit operator bool() const { return hasValue(); }
    void value() const {}
    const std::string& error() const { return std::get<std::string>(data_); }
};

} // namespace flashnotes
