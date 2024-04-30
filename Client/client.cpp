#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <memory>
#include <string>
#include "Client.hpp"
#include "ClientException.hpp"

const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 12345;

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

void onMessageReceived(const std::string &message) {
    std::cout << "Received: " << message << std::endl;
}

void quitSDL() {
    SDLNet_Quit();
    SDL_Quit();
}

int main() {
    initSDL();

    Client client(SERVER_IP, SERVER_PORT);
    client.setReceiveCallback(onMessageReceived);

    try {
        client.connect();
    } catch (const ClientException &e) {
        std::cerr << e.what() << std::endl;
        quitSDL();
        return 1;
    }

    std::string message;
    while (message != "exit") {
        std::cin >> message;
        try {
            client.send(message);
        } catch (const ClientException &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    client.disconnect();
    quitSDL();
    return 0;
}