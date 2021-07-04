#pragma once
#include <iostream>
#define DEBUG_FILE


#ifdef DEBUG_CONSOLE
	#define IMPORT_LOGGER() 
	#define DEBUG_LOG(text) std::cout << text << '\n'
	#define EMBED_LOGGER() AllocConsole();freopen("CONOUT$", "w", stdout);freopen("CONIN$", "r", stdin)
	#define DEFINE_LOGGER()
#endif

#ifdef DEBUG_FILE
	#include <fstream>

	#define IMPORT_LOGGER() extern std::ofstream GBHRC_logger_stream
	#define DEFINE_LOGGER() std::ofstream GBHRC_logger_stream;
	#define EMBED_LOGGER() if(GetFileAttributesA("C:\\GBHRC\\log.log") == INVALID_FILE_ATTRIBUTES) CreateDirectoryA("C:\\GBHRC", nullptr); \
		

	#define DEBUG_LOG(text){GBHRC_logger_stream.open("C:\\GBHRC\\log.log", std::ios::out | std::ios::app); GBHRC_logger_stream << text << '\n';GBHRC_logger_stream.close(); }
#endif

