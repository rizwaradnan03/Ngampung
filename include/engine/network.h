#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET Socket;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    typedef int Socket;
#endif

#include <string>
#include <cstdint>

class Network {
    public:
        Network();
        bool connect_to_server(const std::string& ip, int32_t port);
        void send_data(const std::string& data);
        std::string receive_data();
        ~Network();
    private:
        Socket sock;
};

extern Network* G_network;