#pragma once
#include "../Players/Players.h"

namespace BrokeProtocol {
	namespace Managers {
		class ClManager;

		class ShManager
		{
		public:
		char pad_0000[32]; //0x0000
		Managers::ClManager *clManager; //0x0020
		void *svManager; //0x0028
		char pad_0030[16]; //0x0030
		void *host; //0x0040

		UnityTypes::String* get_version();
		}; //Size: 0x0110

		class SearchingMenu
		{
		public:
			void take_amount(int index,int amount);
		};
		
		class ClManager
		{
		public:
			char pad_0000[24]; //0x0000
			ShManager* manager; //0x0018
			char pad_0020[184]; //0x0020
			Players::ShPlayer* myPlayer; //0x00D8
			char pad_00E0[136]; //0x00E0
			SearchingMenu* searchingMenu; //0x0168
		}; //Size: 0x0110
	}
}
