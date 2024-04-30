#ifndef TEST_RESEAU_CLIENTEXCEPTION_HPP
#define TEST_RESEAU_CLIENTEXCEPTION_HPP

#include <exception>

class ClientException : public std::exception {
public:
    explicit ClientException(const char *message) : message(message) {};

    const char *what() const noexcept override {
        return message;
    }

private:
    const char *message;
};

#endif //TEST_RESEAU_CLIENTEXCEPTION_HPP
