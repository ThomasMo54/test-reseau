#include "Server.hpp"
#include "ServerException.hpp"

Server::~Server() {
    stop();
}

void Server::start() {
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
        throw ServerException(SDLNet_GetError());
    }
    socket = SDLNet_TCP_Open(&ip);
    if (socket == nullptr) {
        throw ServerException(SDLNet_GetError());
    }
    acceptThread = std::make_unique<std::thread>(&Server::acceptConnections, this);
}

void Server::stop() {
    SDLNet_TCP_Close(socket);
    socket = nullptr;
    acceptThread->join();
}

bool Server::isRunning() const {
    return socket != nullptr;
}

void Server::broadcast(const std::string &message) {
    for (TCPsocket client : clients) {
        SDLNet_TCP_Send(client, message.c_str(), message.size() + 1);
    }
}

void Server::setReceiveCallback(void (*callback)(TCPsocket client, const std::string &message)) {
    receiveCallback = callback;
}

void Server::acceptConnections() {
    while (socket) {
        TCPsocket client = SDLNet_TCP_Accept(socket);
        if (client) {
            clients.push_back(client);
            receiveThread = std::make_unique<std::thread>(&Server::receive, this, client);
        }
        SDL_Delay(100);
    }
}

void Server::receive(TCPsocket client) {
    char message[1024];
    while (client) {
        int len = SDLNet_TCP_Recv(client, message, 1024);
        if (len > 0) {
            message[len] = '\0';
            if (receiveCallback) receiveCallback(client, message);
            if (strcmp(message, "exit") == 0) {
                SDLNet_TCP_Close(client);
                client = nullptr;
            }
        }
    }
}
