#include "AuthAssert.h"


#include "../../CheatApi/Socket/GBHRCSocket.h"
#include "../../includes/logger.h"
#include <fstream>
#include <windows.h>

bool cmp_tokens(char*first,char*second,UINT length)
{
    for(UINT i = 0;i < length;i++)
        if (first[i] != second[i])
            return false;

    return true;
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

    DWORD ftyp = GetFileAttributesA(appdata.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;

    std::ifstream ifs(appdata.c_str(), std::fstream::in | std::fstream::binary);
    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    char* token = new char[length];

    ifs.read(token, length);
    DEBUG_LOG(token);
    socket.send_data(token, length);
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

