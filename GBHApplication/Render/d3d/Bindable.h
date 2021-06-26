#pragma once

namespace Application
{
	namespace Render
	{
		class Engine;
		
		class Bindable
		{
		protected:
			Engine* _engine;
		public:
			Bindable(Engine* engine);
			virtual ~Bindable() = default;

			virtual void bind() {};
		};
	}
}


