#include "GBHRCSocket.h"

#include <iostream>
#include <winsock.h>

#define GBHRC_BLOCK_SIZE 12

Network::GBHRCSocket::GBHRCSocket()
{
	_receive_function = [](SOCKET socket,char**buffer)->long
	{
		
		char headers[sizeof(int) * 2+8];
		recv(socket, headers, sizeof(int) * 2 + 8, 0);

		char length_buffer[4] = { headers[0],headers[2],headers[4],headers[6] };
		
		char crypto_buffer[8];
		memcpy(crypto_buffer, &headers[8], 8);
		
		UINT message_size=0;
		memcpy(&message_size, length_buffer, 4);

		UINT to_recv = (message_size / GBHRC_BLOCK_SIZE + 1) * GBHRC_BLOCK_SIZE;

		auto* new_buffer = new char[to_recv];
		
		recv(socket, new_buffer, to_recv, 0);

		for(int i = 0,j=0;i < message_size;i++,j=i%8)
		{
			new_buffer[i] -= crypto_buffer[j];
		}

		*buffer = new_buffer;
		
		return message_size;
	};

	_send_function = [](SOCKET socket, char* buffer, long size)
	{
		send(socket, buffer, size, 0);
	};
}
