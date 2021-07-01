#include "main.h"

#include <iostream>
#include <string>

#include <sstream>
#include <TlHelp32.h>

#define MESALERT(string) MessageBox(0,string,L"ERROR::>",MB_OK)

GBHRCAPI_RESPONSE make_response(BOOL status, const char* response)
{
	GBHRCAPI_RESPONSE _response{status,response};
	return _response;
}

DWORD GBHRCAPI GetProcessId()
{
	int proc_id = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procentry;
		procentry.dwSize = sizeof(procentry);

		if (Process32First(hSnap, &procentry))
		{
			do
			{

				if (wcscmp(procentry.szExeFile, L"BrokeProtocol.exe") == 0)
				{
					proc_id = procentry.th32ProcessID;
					CloseHandle(hSnap);
					break;
				}

			} while (Process32Next(hSnap, &procentry));
		}
	}

	return proc_id;
}

GBHRCAPI_RESPONSE GBHRCAPI Inject()
{
	
	DWORD process_id = GetProcessId();

	if(!process_id)
	{
		return {FALSE,"Cannot find process"};
	}
	

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);

	if (hProc == INVALID_HANDLE_VALUE)
	{
		return {FALSE,"Cannot open process"};
	}

	void* alloc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (alloc == nullptr)
	{
		return {FALSE,"Cannot alloc memory"};
	}
	
	auto* dllname = (LPWSTR)malloc((MAX_PATH+1) * sizeof(wchar_t));

	GetFullPathNameW(L"GBHRC.dll", MAX_PATH * sizeof(wchar_t), dllname, NULL);
	
	if (dllname != nullptr)
		WriteProcessMemory(hProc, alloc, dllname, (wcslen(dllname) + 1)*sizeof(wchar_t), nullptr);
	
	const HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, alloc, 0, 0);
	if (hThread)
		CloseHandle(hThread);
	else
	{
		return {FALSE,"Cannot create remote thread"};
	}


	VirtualFreeEx(hProc, alloc, MAX_PATH, MEM_RELEASE);

	CloseHandle(hProc);

	return make_response(TRUE,"ok");
}

HANDLE FileHandle;

GBHRCAPI_RESPONSE GBHRCAPI SendLuaScript(char*script)
{
	// WriteFile Local Variable Definitions
	BOOL bWriteFile;
	DWORD dwNoBytesWrite;

	const auto dwWriteFileBufferSize = strlen(script)+1;
	
	// WriteFile
	bWriteFile = WriteFile(
		FileHandle,
		script,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL
	);
	if (bWriteFile == FALSE) {
		return { FALSE,"Cannot write file" };
		MESALERT(L"WriteFile has failed with error number: ");
	}
	
	return make_response(TRUE,"ok");
}


GBHRCAPI_RESPONSE GBHRCAPI AttachToProcess()
{
	// CreateFile for Pipe
	FileHandle = CreateFile(
		L"\\\\.\\pipe\\GBHRC",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	
	if (INVALID_HANDLE_VALUE == FileHandle) {
		//std::ostringstream ost;
		//ost << "NamedPipeCreateFile.txt file creation has failed with error number: " << GetLastError();
		//MessageBoxA(0, ost.str().c_str(), "NIGGER", MB_OK);
		return {FALSE,"Cannot open pipe"};
	}
	return {TRUE,"ok"};
}

GBHRCAPI_RESPONSE GBHRCAPI DeAttachFromProcess()
{
	CloseHandle(FileHandle);
	return make_response(TRUE,"ok");
}
