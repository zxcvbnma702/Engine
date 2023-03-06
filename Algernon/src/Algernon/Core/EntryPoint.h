#pragma once

#ifdef AL_PLATFORM_WINDOWS

extern Algernon::Application* Algernon::CreateApplication();

int main(int argc, char** argv) {
	
	Algernon::Log::Init();

	AL_PROFILE_BEGIN_SESSION("StartUp", "AlgernonProfile - Startup.json");
	auto app = Algernon::CreateApplication();
	AL_PROFILE_END_SESSION();

	AL_PROFILE_BEGIN_SESSION("RunTime", "AlgernonProfile - Runtime.json");
	app->Run();
	AL_PROFILE_END_SESSION();

	AL_PROFILE_BEGIN_SESSION("ShutDown", "AlgernonProfile - Shutdown.json");
	delete app;
	AL_PROFILE_END_SESSION();
}
#endif