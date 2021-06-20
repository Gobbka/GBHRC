#include "PipeServer.h"

#include <Windows.h>

#include "../../includes/logger.h"

PipeServer::PipeServer(const char*address)
{
	// NamedPipe Local Variable
	char szInputBuffer[1023];
	char szOutputBuffer[1];
	DWORD dwszInputBuffer = sizeof(szInputBuffer);
	DWORD dwszOutputBuffer = sizeof(szOutputBuffer);

	// CreateNamedPipe - Step 1
	_hCreateNamedPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\GBHRC"),
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	if (_hCreateNamedPipe == INVALID_HANDLE_VALUE) {
		DEBUG_LOG("NamedPipe creation failed with error number: " << GetLastError());
	}
}

PipeServer::~PipeServer()
{
	DisconnectNamedPipe(_hCreateNamedPipe);
	CloseHandle(_hCreateNamedPipe);
}

PipeServer* PipeServer::create(const char* address)
{
	auto* server = new PipeServer(address);
	return server;
}

DWORD PipeServer::receive(char** buffer) const
{
	DWORD dwRead=0;
	std::string wholescript;
	char receive_buffer[256];
	
	if (ConnectNamedPipe(_hCreateNamedPipe, NULL) != FALSE)
	{
		while (ReadFile(_hCreateNamedPipe, receive_buffer, sizeof(receive_buffer) - 1, &dwRead, NULL) != FALSE)
		{
			receive_buffer[dwRead] = '\0';
			wholescript += receive_buffer;
		}

	}
	DisconnectNamedPipe(_hCreateNamedPipe);

	auto length = wholescript.size();
	*buffer = new char[length];
	wholescript.copy(*buffer, length+1);
	(*buffer)[length] = '\0';
	
	return length;
}
