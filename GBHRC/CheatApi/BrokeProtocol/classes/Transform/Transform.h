#pragma once
#include "../../UnityTypes.h"

namespace UnityEngine
{
	class Transform
	{
	public:
		void rotate(float x, float y, float z);
		void lookAt(UnityTypes::Vector3*pos);

		UnityTypes::Vector3* get_position();
		void set_position(UnityTypes::Vector3* vector);
		UnityTypes::Vector3* get_eulerAngles();
	};
}
