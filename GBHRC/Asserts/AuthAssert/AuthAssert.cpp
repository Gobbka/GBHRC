#include "AuthAssert.h"


#include "../../CheatApi/Socket/GBHRCSocket.h"
#include "../../includes/logger.h"
#include <fstream>
#include <windows.h>

bool AuthAssert::check_subscription()
{
    Network::GBHRCSocket socket;

    if (!socket.connect_to("127.0.0.1", 1337))
    {
        DEBUG_LOG("NIGGA WONT CONNECT");
        return false;
    }
    char* nigger;
    socket.receive_to(&nigger);

    delete nigger;
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

    return true;
}
