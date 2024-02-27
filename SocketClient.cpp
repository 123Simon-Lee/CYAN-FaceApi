#include"SocketClient.h"
#include <vector>
#include <cstdint>

 static bool connected = false;
 std::string address = "127.0.0.1";
 int port=8061;
 static std::vector<float> ExpressDat(53,0.0f);
void SocketClient::InitWs2()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return;
    }

    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2) {
        WSACleanup();
        return;
    }
}

void SocketClient::UninitWs32()
{
    WSACleanup();
}


bool SocketClient::SocketCreate()
{
    if (sockClient == INVALID_SOCKET)
    {

        sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sockClient == SOCKET_ERROR)
        {
            printf("socket build failed!\r\n");
            WSACleanup();
            return false;
        }
        else
        {
            printf("socket build Succ!\r\n");
            GetAddressPort(address, port);
                if (!connected)
                {
                    if (connect(sockClient, (sockaddr*)&si, sizeof(si)) == SOCKET_ERROR)
                    {
                        printf("connect failed!\r\n");
                        Close();
                        connected = false;
                        return connected;
                    }
                    else
                    {
                        printf("connect Succs!\r\n");
                        connected = true;
                        SocketSend("Connect Succs!");

                        return connected;
                    }
                }
                else
                    return connected;
           
        }
    }
    else
    {
        GetAddressPort(address, port);
       
            if (!connected)
            {
                if (connect(sockClient, (sockaddr*)&si, sizeof(si)) == SOCKET_ERROR)
                {
                    printf("connect failed!\r\n");
                    //Á¬½ÓÊ§°Ü
                    Close();
                    connected = false;
                    return connected;
                }
                else
                {
                    printf("connect Succs!\r\n");
                    connected = true;

                    return connected;
                }
            }
            else
                return connected;


    }




    return false;
}

void SocketClient::SocketSend(std::string SentSucc)
{
    HEADCALL DL_head;
    DL_head.reqType = 1;
    DL_head.errorType = 0;
    DL_head.v1 = 1;
    WSABUF dataBuf;
    DL_head.len = SentSucc.size();
    char* buffer = new char[sizeof(DL_head) + SentSucc.size()];
    dataBuf.buf = buffer;
    dataBuf.len = sizeof(DL_head) + SentSucc.size();
    memcpy(dataBuf.buf, &DL_head, sizeof(DL_head));
    memcpy(dataBuf.buf + sizeof(DL_head), SentSucc.c_str(), SentSucc.size());

    if (WSASend(sockClient, &dataBuf, 1, &dataBuf.len, 0, NULL, NULL) == SOCKET_ERROR)
    {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;

    }
    else
    {
        printf("Send succ \r\n");
    }
    delete[] buffer;
}
void SocketClient::GetAddressPort(std::string& address, int port) 
{
        sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, address.c_str(), &serverAddr.sin_addr);
        si = serverAddr;
   
}
void SocketClient::SocketRecv()
{
    
    char recvBuffer[1024];


    int readbytes = recv(sockClient, recvBuffer, sizeof(recvBuffer), 0);
    if (readbytes > 0)
    {
        int pshift = 0;
        int len = ReadInt32(recvBuffer, pshift); pshift += 4;
        short reqType = ReadInt16(recvBuffer, pshift); pshift += 2;
        short errorType = ReadInt16(recvBuffer, pshift); pshift += 2;
        pshift += 16;
        if (len > 24)
        {
            CopyFromexpressionStream(recvBuffer, pshift);
            for (int i = 0; i < 53; i++)
            {
                std::cout << "ExpressDat[ " << i << "]:" << ExpressDat[i] << std::endl;
            }
        }
    }
    

    
}
void SocketClient::Close()
{
    if (sockClient != INVALID_SOCKET)
    {
        shutdown(sockClient, SD_BOTH);
        closesocket(sockClient);
        sockClient = INVALID_SOCKET;
    }
}

int SocketClient::ReadInt32(const char* buffer, int offset)
{
    int intValue;
    // Assuming you've checked elsewhere that there's enough data...
    memcpy(&intValue, buffer + offset, sizeof(int));
    return intValue;
}

short SocketClient ::ReadInt16(const char* buffer, int offset)
{
    if (sizeof(buffer) - offset < 2) {
        return 0; // Ensure there's enough data
    }

    short shortValue;
    
    memcpy(&shortValue, buffer + offset, 2);

    return shortValue;
}

float SocketClient::ReadFloat32(const char* buffer, int offset) {
    float int_value;
    uint8_t char_list[4];
    for (int i = 0; i < 4; i++) {
        char_list[i] = static_cast<uint8_t>(buffer[i + offset]);
    }
    std::memcpy(&int_value, char_list, sizeof(float));
   
    return int_value;
}


void SocketClient::CopyFromexpressionStream(const char* buffer, int pshift)
{
    for (int i = 0; i < 53; i++)
    {
        float temp = ReadFloat32(buffer, pshift);
        pshift += sizeof(float); // Advance by the size of a float for the next read
        ExpressDat[i] = temp;
    }
}
