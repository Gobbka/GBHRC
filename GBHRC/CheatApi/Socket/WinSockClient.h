#pragma once
#include <windows.h>

namespace WinSocket
{
	class Client
	{
	public:
		static Client* connect(const char* ip, DWORD port);
		void send(char* data, DWORD size);
		DWORD receive(char** out_data);
	};
}

