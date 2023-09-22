#include "SandBox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

SandBox2D::SandBox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandBox2D::OnAttach()
{
	AL_PROFILE_FUNCTION();

	m_CheckerboardTexture = Algernon::Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach()
{
	AL_PROFILE_FUNCTION();
}

void SandBox2D::OnUpdate(Algernon::Timestep ts)
{
	AL_PROFILE_SCOPE("Sandbox2D::OnUpdate");

	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	Algernon::Renderer2D::ResetStats();
	{
		AL_PROFILE_SCOPE("Renderer Prep");
		Algernon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Algernon::RenderCommand::Clear();
	}
	
	
	{
		AL_PROFILE_SCOPE("Renderer Draw");

		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		Algernon::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Algernon::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Algernon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Algernon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Algernon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Algernon::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Algernon::Renderer2D::EndScene();

		Algernon::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Algernon::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Algernon::Renderer2D::EndScene();
	}
	
}

void SandBox2D::OnImGuiRender()
{
	AL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	auto stats = Algernon::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void SandBox2D::OnEvent(Algernon::Event& e)
{
	m_CameraController.OnEvent(e);
}
