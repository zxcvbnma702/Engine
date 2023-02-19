#pragma once

#ifdef AL_PLATFORM_WINDOWS

extern Algernon::Application* Algernon::CreateApplication();

int main(int argc, char** argv) {
	Algernon::Log::Init();

	auto app = Algernon::CreateApplication();
	app->Run();
	delete app;
}
#endif