#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream> 

// Address of OSPIN server must be configured
const char* REMOTE_HOST = "ADDRESS_OF_THE_OSPIN_SERVER";
const int PORT_RANGE_START = 2000;
const int PORT_RANGE_END = 2010;

int openSsh()
{
    for(int port = PORT_RANGE_START; port <= PORT_RANGE_END; port++) {
        std::stringstream cmd;
        cmd << "service ssh-tunnel start " << port << " " << REMOTE_HOST;
        if(system(cmd.str().c_str()) == 0) {
            return port;
        }
    }
    return -1;
}

int closeSsh()
{
    return system("service ssh-tunnel stop");
}

int main()
{
    // I assume that the implementation of MQTT messaging handling is not required within this 
    // task. So I implemented the function openSsh() which is supposed to be called on 
    // receiving "open-ssh" MQTT message
    // I also implemented closeSsh() function which is supposed to be called, when the appication
    // command recieves MQTT message for closing the tunnel or on the exit of the application. 
    std::string responsePayload;
    int port = openSsh();
    if(port > -1) {
        responsePayload = 
        "{\"port\":" + std::to_string(port) + "\"error\": \"None\"}";
    }
    else {
        responsePayload = 
        "{\"port\": -1,\"error\": \"Unable to establish reverse SSH tunnel\"}";
    }
    std::cout << responsePayload << std::endl;

    //in real world the tunnel shouldn't be closed right away, of course, but the firmware also lives longer than this program.
    closeSsh();
    return 0;
}