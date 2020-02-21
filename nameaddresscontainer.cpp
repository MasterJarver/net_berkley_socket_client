#include "nameaddresscontainer.h"

const int kMaxArgumentCount = 4;
const int kMinArgumentCount = 1;
const int kSize = 1024;
const int kPort = 12345;
const int kWhence = 1024;

bool NameAddressContainer::c_error = false;

NameAddressContainer::NameAddressContainer(int argc, char** argv) : m_fileSize(0)
{
    if(argc <= kMinArgumentCount || argc >= kMaxArgumentCount)
    {
        std::cout << "You must write filename" << std::endl;
        c_error = true;
    }
    else
        m_fileName = argv[1];
    m_fileSize = getFileSize(m_fileName.c_str());
    if(argc >= kMaxArgumentCount - 1)
        m_ip = argv[2];
    else
        m_ip = "127.0.0.1";
    std::cout << m_ip << std::endl;
    m_addr = ip::address::from_string(m_ip);
}

NameAddressContainer::~NameAddressContainer()
{
    std::cout << "destructor" << std::endl;
}

ip::address NameAddressContainer::getIp()
{
    return m_addr;
}

std::string NameAddressContainer::getFileName()
{
    return m_fileName;
}

unsigned long long NameAddressContainer::getSizeFile()
{
    return m_fileSize;
}

bool NameAddressContainer::getError()
{
    return c_error;
}
