/*
* Created by Oleh Korshun
* email: oleh.korshun@gmail.com
*/
#include <iostream>
#include <boost/asio/ip/address.hpp>
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
