
#include"SocketClient.h"



SocketClient* client;
int main()
{
    
    SocketClient socketclient;
    client = &socketclient;
    client->InitWs2();


        while (true)
        {
            if (client->SocketCreate())
            {
              
                client->SocketRecv();
               
            }
            else
            {
               
                std::cout << "connect failed, retry after 5 seconds..." << std::endl;
                Sleep(5000); 
            }

        }
   
    

        client->UninitWs32();
    return 0;
}

