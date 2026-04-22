#include "engine/network.h"
#include "iostream"

Network::Network(){
    #ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa) == 0;
    #endif
}

bool Network::connect_to_server(const std::string& ip, int32_t port){
    sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);

    return connect(sock, (sockaddr*)&server, sizeof(server)) == 0;
}

void Network::send_data(const std::string& data){
    send(sock, data.c_str(), data.size(), 0);
}

std::string Network::receive_data(){
    char buffer[1024];
    int len = recv(sock, buffer, sizeof(buffer), 0);

    if(len <= 0){
        return "";
    }

    return std::string(buffer, len);
}

Network::~Network(){
    #ifdef _WIN32
        closesocket(sock);
        WSACleanup();
    #else
        close(sock);
    #endif
}