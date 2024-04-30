#ifndef TEST_RESEAU_SERVEREXCEPTION_HPP
#define TEST_RESEAU_SERVEREXCEPTION_HPP

#include <exception>

class ServerException : public std::exception {
public:
    explicit ServerException(const char *message) : message(message) {};

    const char *what() const noexcept override {
        return message;
    }

private:
    const char *message;
};

#endif //TEST_RESEAU_SERVEREXCEPTION_HPP
