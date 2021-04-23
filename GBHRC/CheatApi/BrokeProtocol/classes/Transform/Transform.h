#pragma once
#include "../../UnityTypes.h"

namespace UnityEngine
{
	class Transform
	{
	public:
		void rotate(float x, float y, float z);
		void lookAt(UnityTypes::Vector3*pos);
	};
}
