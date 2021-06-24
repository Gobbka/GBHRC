#include "GBHRCSocket.h"

#include <iostream>
#include <winsock.h>

#define GBHRC_BLOCK_SIZE 12

Network::GBHRCSocket::GBHRCSocket()
{
	_receive_function = [](SOCKET socket,char**buffer)->long
	{
		
		char length_buffer[sizeof(int) * 2];
		recv(socket, length_buffer, sizeof(int) * 2, 0);

		UINT message_size=0;
		for(int i = 0;i < sizeof(int);i++)
			length_buffer[i] = length_buffer[i * 2];
		memcpy(&message_size, length_buffer, 4);

		UINT to_recv = (GBHRC_BLOCK_SIZE / message_size + 1) * GBHRC_BLOCK_SIZE;

		*buffer = new char[to_recv];
		recv(socket, *buffer, to_recv, 0);
		
		return message_size;
	};

	_send_function = [](SOCKET socket, char* buffer, long size)
	{
		send(socket, buffer, size, 0);
	};
}
