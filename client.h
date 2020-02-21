#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <boost/asio/ip/address.hpp>
#include <getfilesize.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "nameaddresscontainer.h"
#include <memory>

const int kMaxArgumentCount = 4;
const int kMinArgumentCount = 1;
const int kSize = 1024;
const int kPort = 12345;
const int kWhence = 1024;

class Client
{
public:
    Client(NameAddressContainer& nac);
    ~Client();
    bool fileOpen();
    bool startSocket();
    void sendMetaData();
    void sendFile();
private:
    struct sockaddr_in SockAddr;
    char m_buffer[kSize];
    unsigned long long m_bytes;
    unsigned long long m_fileSize;
    unsigned long long m_fileNameSize;
    std::string m_fileName;
    boost::asio::ip::address m_addr;
    unsigned long long m_bytesCounter;
    std::unique_ptr<FILE> m_file;
    int m_socket;
};

#endif // CLIENT_H
