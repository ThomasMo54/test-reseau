#ifndef TEST_RESEAU_SERVER_HPP
#define TEST_RESEAU_SERVER_HPP

#include <SDL_net.h>
#include <memory>
#include <thread>
#include <vector>

class Server {
public:
    explicit Server(int port): port(port) {};

    ~Server();

    void start();

    void stop();

    bool isRunning() const;

    void broadcast(const std::string &message);

    void setReceiveCallback(void (*callback)(TCPsocket client, const std::string &message));

private:
    const int port;
    TCPsocket socket = nullptr;
    std::vector<TCPsocket> clients;
    std::unique_ptr<std::thread> receiveThread = nullptr;
    std::unique_ptr<std::thread> acceptThread = nullptr;
    void (*receiveCallback)(TCPsocket client, const std::string &message) = nullptr;

    void acceptConnections();

    void receive(TCPsocket client);
};

#endif //TEST_RESEAU_SERVER_HPP
