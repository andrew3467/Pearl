#pragma once

#include "Core.h"


namespace Pearl {
	class PRL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}

