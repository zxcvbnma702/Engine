#include<Algernon.h>

class SandBox : public Algernon::Application {
public:
	SandBox() {
	}
	~SandBox() {
	}
};

Algernon::Application* Algernon::CreateApplication() {
	return new SandBox();
}