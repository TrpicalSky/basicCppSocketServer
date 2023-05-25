#include <boost/asio.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <boost/asio/ip/tcp.hpp>


using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

std::string getData(tcp::socket& socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "");
    std::string data = buffer_cast<const char*>(buf.data());
    return data;
}

void sendData(tcp::socket& socket, const std::string& message) {
    write(socket, buffer(message + "\n"));
}


int main()
{
    
    io_service io;

    // Listening for any new incomming connection
    // at port 9999 with IPv4 protocol
    tcp::acceptor accepter(io, tcp::endpoint(
        tcp::v4(), 9999
    ));

    // Creating socket object
    tcp::socket socketObj(io);

    accepter.accept(socketObj);

    boost::asio::ip::tcp::endpoint localEndpoint = accepter.local_endpoint();
    std::string ipAddress = localEndpoint.address().to_string();
    unsigned short port = localEndpoint.port();

    std::cout << "Server running on IP: " << ipAddress << ", Port: " << port << std::endl;
    


    std::string response;

    while (true) {
        response = getData(socketObj);

        sendData(socketObj, "Recieved");

        if (response == "exit") {
            break;
        }

        std::cout << response << std::endl;
    }
    

    

    return 0;
}