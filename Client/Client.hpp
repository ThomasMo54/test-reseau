#ifndef TEST_RESEAU_CLIENT_HPP
#define TEST_RESEAU_CLIENT_HPP

#include <string>
#include <utility>
#include <thread>
#include <SDL2/SDL_net.h>
#include <SDL_net.h>

class Client {
public:
    explicit Client(std::string ip, int port): ip(std::move(ip)), port(port) {};

    ~Client();

    void connect();

    void disconnect();

    void send(const std::string &message);

    void setReceiveCallback(void (*callback)(const std::string &message));

private:
    const std::string ip;
    const int port;
    TCPsocket socket = nullptr;
    std::unique_ptr<std::thread> receiveThread = nullptr;
    void (*receiveCallback)(const std::string &message) = nullptr;

    void receive();
};

#endif //TEST_RESEAU_CLIENT_HPP
