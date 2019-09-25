#ifndef FDR_UDPSERVER_H
#define FDR_UDPSERVER_H

#include "udpsocket.h"
#include <string>

class UDPServer : public UDPSocket
{
public:
    UDPServer() : UDPSocket()
    {
    }

    void Bind(int port)
    {
        this->Bind("0.0.0.0", port);
    }
    void Bind(const char *address, uint16_t port)
    {
        if (inet_pton(AF_INET, address, &this->address.sin_addr) <= 0)
        {
            if (this->onError)
                this->onError("Error: Invalid address. Address type not supported.");
            perror("inet_pton");
            return;
        }

        this->address.sin_family = AF_INET;
        this->address.sin_port = htons(port);

        if (bind(this->sock, (const sockaddr *)&this->address, sizeof(this->address)) < 0)
        {
            if (this->onError)
                this->onError("Error: Cannot bind the socket.");
            perror("bind");
            return;
        }
    }
};

#endif