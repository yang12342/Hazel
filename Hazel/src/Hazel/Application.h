#pragma once

#include "Core.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to be define in client
	Application* CreateApplication();
};

