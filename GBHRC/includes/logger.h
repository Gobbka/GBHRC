#pragma once
#include <iostream>
#define DEBUG

#ifdef DEBUG
	#define DEBUG_LOG(text) std::cout << text << '\n'
	#define EMBED_LOGGER() AllocConsole();freopen("CONOUT$", "w", stdout);freopen("CONIN$", "r", stdin)
#else
	#define DEBUG_LOG(text)
#endif

