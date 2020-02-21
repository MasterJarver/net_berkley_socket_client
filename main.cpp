/*
* Created by Oleh Korshun
* email: oleh.korshun@gmail.com
*/
#include <iostream>
#include <string>
#include <boost/asio/ip/address.hpp>
#include <getfilesize.h>
#include <unistd.h>
#include <memory>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "nameaddresscontainer.h"
#include "client.h"
#include <memory>

using namespace boost::asio;

int main(int argc, char* argv[])
{
    std::unique_ptr<NameAddressContainer> nac;
    try
    {
        nac.reset(new NameAddressContainer(argc, argv));
    }
    catch(boost::system::system_error& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }
    if(nac->getError() == true)
        return -1;
    Client client(*nac);
    client.fileOpen();
    client.startSocket();
    client.sendMetaData();
    client.sendFile();
    return 0;
}
