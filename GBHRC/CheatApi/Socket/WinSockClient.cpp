#include "WinSockClient.h"
#include <WS2tcpip.h>
#include <iostream>
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "Ws2_32.lib")


bool Network::WinClient::connect_to(const char* ip, long port)
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	auto wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		return false;
	}

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ip, &hint.sin_addr);

	// Connect to server
	auto connResult = connect(_socket, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		closesocket(_socket);
		WSACleanup();
		return false;
	}

	return true;
}

void Network::WinClient::send_data(char* data, long size) const
{
	send(_socket, data, size, 0);
}

long Network::WinClient::receive_from(char** out_data) const
{
	return _receive_function(_socket,out_data);
}

Network::WinClient::WinClient()
{
	_receive_function = [](SOCKET socket,char**)->long
	{
		return 0;
	};
}

Network::WinClient::~WinClient()
{
	closesocket(_socket);
	WSACleanup();
}
