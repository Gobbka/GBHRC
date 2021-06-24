#include "WinSockClient.h"
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

WinSocket::Client* WinSocket::Client::connect(const char* ip, DWORD port)
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	auto wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		return nullptr;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ip, &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		closesocket(sock);
		WSACleanup();
		return;
	}
}
