#include "main.h"

#include <iostream>
#include <TlHelp32.h>


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

BOOL SendLuaScript()
{
	using namespace std;
	// Local Variable Definitions
	HANDLE hCreateFile;

	// ReadFile Local Variable Definitions
	BOOL bReadFile;
	DWORD dwNoBytesRead;
	char szReadFileBuffer[1023];
	DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);

	// WriteFile Local Variable Definitions
	BOOL bWriteFile;
	DWORD dwNoBytesWrite;
	char szWriteFileBuffer[1023] = "Hello from NamedPipe Client!";
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	// CreateFile for Pipe
	hCreateFile = CreateFile(
		L"\\\\.\\pipe\\MYNAMEDPIPE228",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (INVALID_HANDLE_VALUE == hCreateFile) {
		cout << "NamedPipeCreateFile.txt file creation has failed with error number: " << GetLastError() << endl;
	}
	cout << "NamedPipeCreateFile.txt file creation is successful" << endl;

	// WriteFile
	bWriteFile = WriteFile(
		hCreateFile,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL
	);
	if (bWriteFile == FALSE) {
		cout << "WriteFile has failed with error number: " << GetLastError() << endl;
	}
	
	return TRUE;
}
