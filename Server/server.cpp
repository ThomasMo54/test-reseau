#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include "Server.hpp"
#include "ServerException.hpp"

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

void onMessageReceived(TCPsocket client, const std::string &message) {
    std::cout << "Received: " << message << std::endl;
}

void quitSDL() {
    SDLNet_Quit();
    SDL_Quit();
}

int main() {
    initSDL();

    Server server(SERVER_PORT);
    server.setReceiveCallback(onMessageReceived);

    try {
        server.start();
    } catch (const ServerException &e) {
        std::cerr << e.what() << std::endl;
        quitSDL();
        return 1;
    }

    while (server.isRunning()) {
        server.broadcast("Hello!");
        std::cout << "Broadcast: Hello!" << std::endl;
        SDL_Delay(1000);
    }

    quitSDL();
    return 0;
}