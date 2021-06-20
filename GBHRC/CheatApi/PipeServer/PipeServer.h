#pragma once
#include <Windows.h>
class PipeServer
{

private:
	PipeServer(const char* address);
	~PipeServer();

	HANDLE _hCreateNamedPipe;
	
public:
	
	static PipeServer* create(const char* address);
	DWORD receive(char**buffer) const;
};
