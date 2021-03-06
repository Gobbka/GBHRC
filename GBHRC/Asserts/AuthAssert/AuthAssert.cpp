#include "AuthAssert.h"


#include "../../CheatApi/Socket/GBHRCSocket.h"
#include "../../includes/logger.h"
#include <fstream>
#include <cstdio>
#include <ctime>
#include <intrin.h>
#include <windows.h>

IMPORT_LOGGER();

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
    if (!socket.connect_to("194.93.2.84", 1337))
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

    const UINT salt_size = sizeof(short) * 4;
	
    auto* token = new char[salt_size + length + hwid_size];
    auto* original_token = new char[length];

    srand((unsigned)time(0));

    for(int i = 0;i < 4;i++)
    {
        short random = (short)rand();
        memcpy(token + i * sizeof(random), &random, sizeof(random));
    }
	
    ifs.read(original_token, length);

    memcpy(token + salt_size, original_token, length);
    
	
    memcpy(token + length + salt_size, hwid, hwid_size);

	for(int i =0,j=0;i < salt_size + length + hwid_size - 8;i++,j = i % 8)
	{
        token[i + 8] += token[j];
	}
 
    socket.send_data(token, salt_size + length + hwid_size - 1);
    // compare tokens
	
    char* nigger;
    auto rec_token_size = socket.receive_to(&nigger);

    if (!cmp_tokens(original_token, nigger, min(rec_token_size,length)))
    {
        free(nigger);
        return false;
    }

    free(nigger);
    free(original_token);
    free(token);
    return true;
}

