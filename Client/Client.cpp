#include "Client.hpp"
#include "ClientException.hpp"

Client::~Client() {
    disconnect();
}

void Client::connect() {
    IPaddress ipAddress;
    if (SDLNet_ResolveHost(&ipAddress, ip.c_str(), port) == -1) {
        throw ClientException(SDLNet_GetError());
    }
    socket = SDLNet_TCP_Open(&ipAddress);
    if (!socket) {
        throw ClientException(SDLNet_GetError());
    }
    receiveThread = std::make_unique<std::thread>(std::thread(&Client::receive, this));
}

void Client::disconnect() {
    SDLNet_TCP_Close(socket);
    socket = nullptr;
}

void Client::send(const std::string &message) {
    if (SDLNet_TCP_Send(socket, message.c_str(), message.size() + 1) == -1) {
        throw ClientException(SDLNet_GetError());
    }
}

void Client::setReceiveCallback(void (*callback)(const std::string &message)) {
    receiveCallback = callback;
}

void Client::receive() {
    char message[1024];
    while (socket) {
        int len = SDLNet_TCP_Recv(socket, message, 1024);
        if (len > 0) {
            message[len] = '\0';
            if (receiveCallback) receiveCallback(message);
        }
    }
}
