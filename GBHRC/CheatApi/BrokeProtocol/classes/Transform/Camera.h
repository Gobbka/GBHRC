#pragma once
#include "../../UnityTypes.h"

namespace UnityEngine
{
	class Camera
	{
	public:
		UnityTypes::Vector3* WorldToScreenPoint(UnityTypes::Vector3* pos);
	};
}

