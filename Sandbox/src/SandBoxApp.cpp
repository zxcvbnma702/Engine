#include<Algernon.h>

class SandBox : public Algernon::Application {
public:
	SandBox() {
		PushOverlay(new Algernon::ImGuiLayer());
	}
	~SandBox() {
	}
};

Algernon::Application* Algernon::CreateApplication() {
	return new SandBox();
}