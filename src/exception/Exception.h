#ifndef FIN_CALCULATOR_EXCEPTION_H
#define FIN_CALCULATOR_EXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class Exception : public std::exception
{
public:
    Exception(std::string message) : message(std::move(message)){};
    [[nodiscard]] const char *what() const noexcept override;

private:
    std::string message;
};

#endif // FIN_CALCULATOR_EXCEPTION_H