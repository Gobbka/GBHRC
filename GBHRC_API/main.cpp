#include "main.h"

#include <iostream>
#include <string>

#include <sstream>
#include <TlHelp32.h>

#define MESALERT(string) MessageBox(0,string,L"ERROR::>",MB_OK)

DWORD GetProcessId()
{
	int proc_id = 0;

	while (1)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 procentry;
			procentry.dwSize = sizeof(procentry);

			if (Process32First(hSnap, &procentry))
			{
				do
				{

					if (_stricmp((char*)procentry.szExeFile, "BrokeProtocol.exe") == 0)
					{
						proc_id = procentry.th32ProcessID;
						CloseHandle(hSnap);
						break;
					}

				} while (Process32Next(hSnap, &procentry));
			}
		}

		if (proc_id != NULL)
			break;
		Sleep(500);
	}
	return proc_id;
}

BOOL inject()
{

	DWORD process_id = GetProcessId();
	if(process_id)
	{
		MessageBox(0, L"INJECTION ERROR", L"Process cannot be found", MB_OK | MB_ICONERROR);
		return false;
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);

	if (hProc == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}

	void* alloc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (alloc == nullptr)
	{
		return EXIT_FAILURE;
	}

	char* dllname = (char*)malloc(MAX_PATH);

	GetFullPathName(L"GBHRC.dll", MAX_PATH, (LPWSTR)dllname, NULL);

	if (dllname != nullptr)
		WriteProcessMemory(hProc, alloc, dllname, strlen(dllname) + 1, nullptr);

	const HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, alloc, 0, 0);
	if (hThread)
		CloseHandle(hThread);
	else
	{
		return 0;
	}

	VirtualFreeEx(hProc, alloc, MAX_PATH, MEM_RELEASE);

	CloseHandle(hProc);

	return EXIT_SUCCESS;
}

HANDLE FileHandle;

BOOL SendLuaScript(char*script)
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
		MESALERT(L"WriteFile has failed with error number: ");
	}
	
	return TRUE;
}


BOOL AttachToProcess()
{
	// CreateFile for Pipe
	FileHandle = CreateFile(
		L"\\\\.\\pipe\\MYNAMEDPIPE228",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	
	if (INVALID_HANDLE_VALUE == FileHandle) {
		std::ostringstream ost;
		ost << "NamedPipeCreateFile.txt file creation has failed with error number: " << GetLastError();
		MessageBoxA(0, ost.str().c_str(), "NIGGER", MB_OK);
		return false;
	}
	return true;
}

BOOL DeAttachFromProcess()
{
	CloseHandle(FileHandle);
	return TRUE;
}
