#include "client.h"

Client::Client(NameAddressContainer& nac) : m_bytes(0), m_bytesCounter(0)
{
    m_addr = nac.getIp();
    m_fileName = nac.getFileName();
    m_fileNameSize = m_fileName.size();
    m_fileSize = nac.getSizeFile();
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(kPort);
    SockAddr.sin_addr.s_addr = inet_addr(m_addr.to_string().c_str());
}

Client::~Client()
{

}

bool Client::fileOpen()
{
    m_file.reset(fopen(m_fileName.c_str(), "r+b"));
    if(m_file.get() == nullptr)
    {
        std::cout << "error open file" << std::endl;
        return false;
    }
    return true;
}

bool Client::startSocket()
{
    int socketConnect = connect(m_socket, (struct sockaddr*)(&SockAddr), sizeof(SockAddr));
    if(socketConnect != 0)
    {
        std::cout << "Error connect" << std::endl;
        fclose(m_file.get());
        return false;
    }
    else
        return true;
}

void Client::sendMetaData()
{
    std::cout << "sending size file: " << m_fileSize << std::endl;
    send(m_socket, &m_fileSize, sizeof(m_fileSize), MSG_NOSIGNAL); // send file size
    std::cout << "sending file name size : " << m_fileName.size() << std::endl;
    send(m_socket, &m_fileNameSize, sizeof(m_fileNameSize), MSG_NOSIGNAL); // send file name size
    std::cout << "sending file name : " << m_fileName << std::endl;
    send(m_socket, m_fileName.c_str(), m_fileName.size(), MSG_NOSIGNAL); // send file name
    std::cout << "begin senging file..." << std::endl;
}

void Client::sendFile()
{
    while(m_bytesCounter != m_fileSize)
    {
        fseek(m_file.get(), m_bytesCounter, SEEK_SET);
        m_bytes = (unsigned long long)fread(m_buffer, 1, kWhence, m_file.get());
        std::cout << "read bytes: " << m_bytes << std::endl;
        m_bytes = (unsigned long long)send(m_socket, m_buffer, m_bytes,  MSG_NOSIGNAL);
        std::cout << "send bytes: " << m_bytes << std::endl;
        m_bytesCounter += m_bytes;
        std::cout << "bytes: " << m_bytesCounter << std::endl;
        if(m_bytesCounter == m_fileSize)
        {
            std::cout << "all file send bytes: " << m_bytesCounter << std::endl;
            fclose(m_file.get());
        }
    }
    std::cout << "end program." << std::endl;
    shutdown(m_socket, SHUT_RDWR);
    close(m_socket);
    std::cout << "=========client=========" << std::endl;
}
