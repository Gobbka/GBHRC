#include "main.h"
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

	GetFullPathName(L"GBP.dll", MAX_PATH, (LPWSTR)dllname, NULL);

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

BOOL lua_send()
{
	return FALSE;
}
