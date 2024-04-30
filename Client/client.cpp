#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <memory>

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

std::unique_ptr<TCPsocket> initClient() {
    std::cout << "Connecting to server..." << std::endl;
    IPaddress ip;
    TCPsocket client;
    if (SDLNet_ResolveHost(&ip, SERVER_IP, SERVER_PORT) == -1) {
        std::cerr << "SDLNet_ResolveHost Error: " << SDLNet_GetError() << std::endl;
        exit(1);
    }
    client = SDLNet_TCP_Open(&ip);
    if (!client) {
        std::cerr << "SDLNet_TCP_Open Error: " << SDLNet_GetError() << std::endl;
        exit(1);
    }
    std::cout << "Connected to server" << std::endl;
    return std::make_unique<TCPsocket>(client);
}

void handleCommunication(std::unique_ptr<TCPsocket> &client) {
    char message[1024] = "Hello!";
    SDLNet_TCP_Send(*client, message, strlen(message) + 1);
    std::cout << "Received: " << message << std::endl;
    char received[1024];
    int len = SDLNet_TCP_Recv(*client, received, 1024);
    if (len > 0) {
        received[len] = '\0';
        std::cout << "Received: " << received << std::endl;
    }
}

void closeClient() {
    SDLNet_Quit();
    SDL_Quit();
}

int main() {
    initSDL();
    std::unique_ptr<TCPsocket> client = initClient();
    handleCommunication(client);
    closeClient();
    return 0;
}