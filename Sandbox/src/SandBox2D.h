#pragma once

#include "Algernon.h"

class SandBox2D : public Algernon::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Algernon::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Algernon::Event& e) override;
private:
	Algernon::OrthographicCameraController m_CameraController;

	// Temp
	Algernon::Ref<Algernon::VertexArray> m_SquareVA;
	Algernon::Ref<Algernon::Shader> m_FlatColorShader;
	Algernon::Ref<Algernon::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

