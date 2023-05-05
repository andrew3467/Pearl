#pragma once

#ifdef PRL_PLATFORM_WINDOWS

extern Pearl::Application* Pearl::CreateApplication();

int main(int argc, char** argv) 
{

	Pearl::Log::Init();

	PRL_CORE_ERROR("initialized core logger");
	auto a = 5;
	PRL_INFO("initialized client logger, var = {0}", a);
	
	auto app = Pearl::CreateApplication();
	app->Run();

	delete app;
}

#endif