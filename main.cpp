
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
                // 连接失败，等待一段时间后重新连接
                std::cout << "connect failed, retry after 5 seconds..." << std::endl;
                Sleep(5000); // 等待 5 秒
            }

        }
   
    

        client->UninitWs32();
    return 0;
}

