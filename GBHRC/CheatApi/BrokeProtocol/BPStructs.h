#include <cstdint>
#include "UnityTypes.h"
#include "classes/Transform/Transform.h"
#include "classes/Transform/Camera.h"

namespace UnityEngine {
	class Camera;
	class Transform;
}


namespace BrokeProtocol {
	namespace Managers {
		class ClManager;
		class ShManager;
	}
}

namespace BrokeProtocol {
	namespace Players {
		class ClPlayer;
		class ShPlayer;
	}
}

namespace BrokeProtocol {
	namespace Structs {

		class MainCamera
		{
		public:
			char pad_0000[48]; //0x0000
			UnityEngine::Transform* worldCameraT; //0x0030
			UnityEngine::Camera* worldCamera; //0x0038
			char pad_0040[24]; //0x0040
			Managers::ClManager* ClManager; //0x0058
			Players::ShPlayer* ShPlayer; //0x0060
		};

		class Location
		{
		public:
			char pad_0000[32]; //0x0000
			float oX; //0x0020
			float oY; //0x0024
			float oZ; //0x0028
			char pad_002C[28]; //0x002C
		}; //Size: 0x0048

		class Mountable
		{
		public:
			char pad_0000[304]; //0x0000
			float health; //0x0130
			float maxHealth; //0x0134
			char pad_0138[72]; //0x0138
			float maxSpeed; //0x0180
			char pad_0184[132]; //0x0184
		}; //Size: 0x0208

		class Equipable
		{
		public:
			char pad_0000[32]; //0x0000
			void* clEntity; //0x0020
			void* svEntity; //0x0028
			char pad_0030[60]; //0x0030
			uint32_t itemId; //0x006C
			char pad_0070[16]; //0x0070
			bool isHuman; //0x0080
			bool isWorldEntity; //0x0081
			bool hasInventory; //0x0082
			bool shop; //0x0083
			uint32_t ID; //0x0084
			uint32_t index; //0x0088
			int32_t Value; //0x008C
			char pad_0090[144]; //0x0090
			uint32_t cannot_shoot; //0x0120
			char pad_0124[156]; //0x0124
			uint32_t damage; //0x01C0
			char pad_01C4[8]; //0x01C4
		}; //Size: 0x01CC

		class GlobalTypes
		{
		public:
			char pad_0000[16]; //0x0000
			Players::ShPlayer* player; //0x0010
			Players::ClPlayer* clPlayer; //0x0018
			Managers::ShManager* manager; //0x0020
			Managers::ClManager* clManager; //0x0028
		};

		class Evaluator
		{
		public:
			char pad_0000[16]; //0x0000
			void* ScriptDict; //0x0010
			char pad_0018[24]; //0x0018
			GlobalTypes* GlobalTypes; //0x0030
		};
	}
}
