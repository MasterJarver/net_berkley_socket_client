#ifndef NAMEADRESSCONTAINER_H
#define NAMEADRESSCONTAINER_H

#include <iostream>
#include <string>
#include <boost/asio/ip/address.hpp>
#include "getfilesize.h"

using namespace boost::asio;

class NameAddressContainer
{
public:
    NameAddressContainer(int argc, char* argv[]);
    ~NameAddressContainer();
    ip::address getIp();
    std::string getFileName();
    unsigned long long getSizeFile();
    static bool getError();
private:
    static bool c_error;
    std::string m_fileName;
    std::string m_ip;
    ip::address m_addr;
    unsigned long long m_fileSize;
};

#endif // NAMEADRESSCONTAINER_H
