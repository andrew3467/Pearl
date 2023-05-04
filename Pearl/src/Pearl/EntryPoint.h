#pragma once

#ifdef PRL_PLATFORM_WINDOWS

extern Pearl::Application* Pearl::CreateApplication();

int main(int argc, char** argv) {
	
	auto app = Pearl::CreateApplication();
	app->Run();

	delete app;
}

#endif