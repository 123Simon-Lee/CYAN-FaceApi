#pragma once
#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#define SERVER_PORT 8065	//¶Ë¿ÚºÅ
#include <iostream>
#include"sys/types.h"
#include <windows.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include<cstdint>
#include <vector>
#include <cstdint> // For uint8_t
#include <cstring> // For memcpy

typedef struct
{
    int           len;
    short         reqType;
    short         errorType;
    short         v1;
}HEADCALL;


class SocketClient
{
private:
    sockaddr_in si{};
    SOCKET sockClient;
public:
    SocketClient() :sockClient(INVALID_SOCKET) {};
    virtual ~SocketClient() { Close(); }
    void InitWs2();
    void UninitWs32();
    bool SocketCreate();
    void GetAddressPort(std::string& address, int port);
    void SocketSend(std::string SentSucc);
    void SocketRecv();
    void Close();

    int ReadInt32(const char* buffer, int offset);

    short ReadInt16(const char* buffer, int offset);

    float ReadFloat32(const char* buffer, int offset);
    void CopyFromexpressionStream(const char* buffer, int pshift);
    
};