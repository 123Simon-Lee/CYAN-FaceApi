
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
                // ����ʧ�ܣ��ȴ�һ��ʱ�����������
                std::cout << "connect failed, retry after 5 seconds..." << std::endl;
                Sleep(5000); // �ȴ� 5 ��
            }

        }
   
    

        client->UninitWs32();
    return 0;
}

