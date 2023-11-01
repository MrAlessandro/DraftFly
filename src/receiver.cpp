#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int PORT = 12345;
const char *BROADCAST_IP = "0.0.0.0"; // Indirizzo IP speciale per ricevere tutti i pacchetti in arrivo.

namespace draftfly
{

    void receiveMessages()
    {
        int broadcastSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (broadcastSocket == -1)
        {
            perror("socket");
            exit(1);
        }

        struct sockaddr_in broadcastAddr;
        memset(&broadcastAddr, 0, sizeof(broadcastAddr));
        broadcastAddr.sin_family = AF_INET;
        broadcastAddr.sin_port = htons(PORT);
        inet_pton(AF_INET, BROADCAST_IP, &(broadcastAddr.sin_addr));

        if (bind(broadcastSocket, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) == -1)
        {
            perror("bind");
            close(broadcastSocket);
            exit(1);
        }

        while (true)
        {
            char buffer[1024];
            struct sockaddr_in senderAddr;
            socklen_t senderAddrLen = sizeof(senderAddr);

            ssize_t bytesRead = recvfrom(broadcastSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderAddrLen);
            if (bytesRead == -1)
            {
                perror("recvfrom");
            }
            else
            {
                buffer[bytesRead] = '\0';
                std::cout << "Messaggio ricevuto da " << inet_ntoa(senderAddr.sin_addr) << ": " << buffer << std::endl;
            }
        }

        close(broadcastSocket);
    }

} // namespace draftfly
