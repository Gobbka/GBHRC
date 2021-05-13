#include "ClientVersionAssers.h"
#include <Windows.h>

#include "../../CheatApi/BrokeProtocol/BrokeProtocol.h"
#include "../../includes/clientdefs.h"


bool ClientVersionAsserts::check_bp_version()
{

	
    if (wcscmp(BrokeProtocol::get_manager()->get_version()->array, CLIENT_LAST_VERSION_STR) != 0)
    {
        auto code = MessageBox(0,
            L"Seems that modification outdated :/\nDownload new version from our official discord: " DISCORD_CHANNEL "\n(CLICK OK FOR COPY)",
            L"modification outdated!",
            MB_OKCANCEL | MB_ICONERROR
        );

        if (code == IDOK)
        {
            OpenClipboard(0);
            EmptyClipboard();
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(DISCORD_CHANNEL) + 1);
            if (!hg) {
                CloseClipboard();
                return false;
            }
            memcpy(GlobalLock(hg), DISCORD_CHANNEL, strlen(DISCORD_CHANNEL) + 1);
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
            CloseClipboard();
            GlobalFree(hg);
        }
        return false;
    }

    return true;
}
