#include "AuthAssert.h"


#include "../../CheatApi/Socket/GBHRCSocket.h"
#include "../../includes/logger.h"
#include <fstream>
#include <cstdio>
#include <intrin.h>
#include <windows.h>

bool cmp_tokens(char*first,char*second,UINT length)
{
    for(UINT i = 0;i < length;i++)
        if (first[i] != second[i])
            return false;

    return true;
}

char* create_hwid(int*size)
{
    int cpuid[4];
    __cpuid(cpuid,1);

    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey);
    if (lRes != ERROR_SUCCESS)
        return nullptr;

    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG error = RegQueryValueExW(hKey, L"BaseBoardProduct", nullptr, 0, (LPBYTE)szBuffer, &dwBufferSize);
	
    if (error != ERROR_SUCCESS)
        return nullptr;

    const auto length = sizeof(cpuid) + dwBufferSize + 4;
    const auto token = new char[length];

    memcpy(token, &cpuid[3], 2);
    memcpy(token + 2, &cpuid[2], 2);
    memcpy(token + 4, cpuid, sizeof(cpuid));
    memcpy(token + 4 + sizeof(cpuid), szBuffer, dwBufferSize);

	for(int i =0,j=0;i < sizeof(cpuid)+dwBufferSize;i++,j=i%4)
	{
        token[i + 4] += token[j];
	}
    *size = length;
	return token;
}

bool AuthAssert::check_subscription()
{
    Network::GBHRCSocket socket;
    // 194.93.2.84
    if (!socket.connect_to("127.0.0.1", 1337))
    {
        DEBUG_LOG("NIGGA WONT CONNECT");
        return false;
    }

    // getting token
    std::string appdata = getenv("APPDATA");
    appdata += "\\gbhrc\\.ini";

    int hwid_size;
    auto*hwid = create_hwid(&hwid_size);
    if (hwid == nullptr)
        return false;

    DWORD ftyp = GetFileAttributesA(appdata.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;

    std::ifstream ifs(appdata.c_str(), std::fstream::in | std::fstream::binary);
    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    auto* token = new char[length + hwid_size];

    ifs.read(token, length);

    memcpy(token + length, hwid, hwid_size);
    DEBUG_LOG(token);
    socket.send_data(token, length + hwid_size);
    // compare tokens
	
    char* nigger;
    auto rec_token_size = socket.receive_to(&nigger);

    if (!cmp_tokens(token, nigger, min(rec_token_size,length)))
    {
        free(nigger);
        return false;
    }

    free(nigger);
    return true;
}

