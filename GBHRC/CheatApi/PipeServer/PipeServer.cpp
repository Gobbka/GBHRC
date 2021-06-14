#include "PipeServer.h"

#include <Windows.h>

#include "../../includes/logger.h"

PipeServer::PipeServer(const char*address)
{
	// NamedPipe Local Variable
	char szInputBuffer[1023];
	char szOutputBuffer[1023];
	DWORD dwszInputBuffer = sizeof(szInputBuffer);
	DWORD dwszOutputBuffer = sizeof(szOutputBuffer);

	// ConnectNamedPipe Local Variable
	BOOL bConnectNamedPipe;

	// WriteFile Local Variable
	BOOL bWriteFile;
	char szWriteFileBuffer[1023] = "Hello from NamedPipe Server!";
	DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesWrite;

	// Flush Buffer
	BOOL bFlushFileBuffer;

	// ReadFile Local Variable
	BOOL bReadFile;
	char szReadFileBuffer[1023];
	DWORD dwReadBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesRead;

	// CreateNamedPipe - Step 1
	hCreateNamedPipe = CreateNamedPipe(
		L"\\\\.\\pipe\\MYNAMEDPIPE228",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		dwszOutputBuffer,
		dwszInputBuffer,
		0,
		NULL
	);

	if (hCreateNamedPipe == INVALID_HANDLE_VALUE) {
		DEBUG_LOG("NamedPipe creation failed with error number: " << GetLastError());
	}
}

PipeServer::~PipeServer()
{
	DisconnectNamedPipe(hCreateNamedPipe);
	CloseHandle(hCreateNamedPipe);
}

PipeServer* PipeServer::create(const char* address)
{
	auto* server = new PipeServer(address);
	return server;
}

DWORD PipeServer::receive(char* buffer, unsigned int size)
{
	// Flush the File Buffer - Step 4
	if (FlushFileBuffers(hCreateNamedPipe) == FALSE) {
		DEBUG_LOG("FlushFileBuffer failed with error number: " << GetLastError());
	}

	// ReadFile - Step 5
	DWORD bytes_readed = 0;
	if (ReadFile(
		hCreateNamedPipe,
		buffer,
		size,
		&bytes_readed,
		NULL
	) == FALSE) {
		return 0;
	}

	DEBUG_LOG("DATA READING FROM CLIENT -> " << buffer);
	
	return bytes_readed;
}
