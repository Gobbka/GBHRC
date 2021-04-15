#pragma once
#include "../Players/Players.h"

namespace BrokeProtocol {
	namespace Managers {

		class ShManager
		{
		public:
			char pad_0000[24]; //0x0000
			class ClManager* clManager; //0x0018
			char(*svManager)[4]; //0x0020
			char pad_0028[232]; //0x0028
		}; //Size: 0x0110

		class ClManager
		{
		public:
			char pad_0000[24]; //0x0000
			class ShManager* manager; //0x0018
			char pad_0020[184]; //0x0020
			Players::ShPlayer* myPlayer; //0x00D8
			char pad_00E0[48]; //0x00E0
		}; //Size: 0x0110
	}
}
