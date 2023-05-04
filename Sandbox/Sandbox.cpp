#include <Pearl.h>


class Sandbox : public Pearl::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Pearl::Application* Pearl::CreateApplication() {
	return new Sandbox();
}