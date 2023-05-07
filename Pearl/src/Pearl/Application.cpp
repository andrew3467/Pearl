#include "Application.h"

#include "Pearl/Events/ApplicationEvent.h"
#include "Pearl/Log.h"


namespace Pearl {
	
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		PRL_TRACE(e);


		while (true);
	}
}
