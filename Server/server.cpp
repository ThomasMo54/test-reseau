#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <memory>

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (SDLNet_Init() == -1) {
        std::cerr << "SDLNet_Init Error: " << SDLNet_GetError() << std::endl;
        exit(1);
    }
}

std::unique_ptr<TCPsocket> initServer() {
    std::cout << "Starting server..." << std::endl;
    IPaddress ip;
    TCPsocket server;
    if (SDLNet_ResolveHost(&ip, nullptr, 12345) == -1) {
        std::cerr << "SDLNet_ResolveHost Error: " << SDLNet_GetError() << std::endl;
        exit(1);
    }
    server = SDLNet_TCP_Open(&ip);
    if (!server) {
        std::cerr << "SDLNet_TCP_Open Error: " << SDLNet_GetError() << std::endl;
        exit(1);
    }
    std::cout << "Server started" << std::endl;
    return std::make_unique<TCPsocket>(server);
}

std::unique_ptr<TCPsocket> acceptClient(std::unique_ptr<TCPsocket> &server) {
    TCPsocket client = nullptr;
    while (!client) {
        client = SDLNet_TCP_Accept(*server);
        SDL_Delay(100);
    }
    std::cout << "Client connected" << std::endl;
    return std::make_unique<TCPsocket>(client);
}

void handleCommunication(std::unique_ptr<TCPsocket> &client) {
    char message[1024];
    while (strcmp(message, "exit")) {
        int len = SDLNet_TCP_Recv(*client, message, 1024);
        if (len > 0) {
            message[len] = '\0';
            std::cout << "Received: " << message << std::endl;
        }
        SDLNet_TCP_Send(*client, message, len);
    }
}

void closeServer() {
    SDLNet_Quit();
    SDL_Quit();
}

int main() {
    initSDL();
    std::unique_ptr<TCPsocket> server = initServer();
    std::unique_ptr<TCPsocket> client = acceptClient(server);
    handleCommunication(client);
    closeServer();
    return 0;
}