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
			char pad_0000[24]; //0x0000
			UnityEngine::Camera* firstPersonPrefab; //0x0018
			UnityEngine::Transform* Transform; //0x0020
			UnityEngine::Camera* AnotherCamera; //0x0028
			UnityEngine::Transform* WorldCameraT; //0x0030
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
			char pad_0000[392]; //0x0000
			float maxSpeed; //0x0188
			float speedLimit; //0x018C
			char pad_0190[4]; //0x0190
		}; //Size: 0x0208

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

		class StanceType
		{
		public:
			char pad_0000[16]; //0x0000
			uint32_t index; //0x0010
			float capsuleHeight; //0x0014
			float offset; //0x0018
			float input; //0x001C
			bool setable; //0x0020
			bool ragdoll; //0x0021
			bool fixedForward; //0x0022
		}; //Size: 0x0023
	}
}
