#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace draftfly
{

    const int PORT = 12345;
    const char *BROADCAST_IP = "255.255.255.255";

    void sendMessage(const std::string &message)
    {
        int broadcastSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (broadcastSocket == -1)
        {
            perror("socket");
            exit(1);
        }

        int broadcastEnable = 1;
        if (setsockopt(broadcastSocket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) == -1)
        {
            perror("setsockopt");
            close(broadcastSocket);
            exit(1);
        }

        struct sockaddr_in broadcastAddr;
        memset(&broadcastAddr, 0, sizeof(broadcastAddr));
        broadcastAddr.sin_family = AF_INET;
        broadcastAddr.sin_port = htons(PORT);
        inet_pton(AF_INET, BROADCAST_IP, &(broadcastAddr.sin_addr));

        if (sendto(broadcastSocket, message.c_str(), message.length(), 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) == -1)
        {
            perror("sendto");
        }

        close(broadcastSocket);
    }
}


