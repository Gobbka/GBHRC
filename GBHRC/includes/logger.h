#pragma once
#include <iostream>
#define DEBUG

#ifdef DEBUG
	#define DEBUG_LOG(text) std::cout << text << '\n'
#else
	#define DEBUG_LOG(text)
#endif

